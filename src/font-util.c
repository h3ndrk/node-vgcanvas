/**
 * Copyright (C) 2015 NIPE-SYSTEMS
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "include-core.h"
#include "include-openvg.h"
#include "include-freetype.h"

#include "font-util.h"

#define SEGMENTS_COUNT_MAX 256
#define COORDS_COUNT_MAX 1024
#define FONT_FLOAT_FROM_26_6(x) ((VGfloat)x / 64.0f)

static FT_Library font_library = NULL;
static font_t *fonts = NULL;
static int fonts_amount = 0;

static VGuint segments_count;
static VGubyte segments[SEGMENTS_COUNT_MAX];
static VGuint coords_count;
static VGfloat coords[COORDS_COUNT_MAX];

static void convert_contour(const FT_Vector *points, const char *tags, short points_count)
{
	int first_coords = coords_count;
	
	int first = 1;
	char last_tag = 0;
	int c = 0;
	
	for (; points_count != 0; ++points, ++tags, --points_count)
	{
		++c;
		
		char tag = *tags;
		if(first)
		{
			assert(tag & 0x1);
			assert(c==1); c=0;
			segments[segments_count++] = VG_MOVE_TO;
			first = 0;
		}
		else if(tag & 0x1)
		{
			/* on curve */
			
			if (last_tag & 0x1)
			{
				/* last point was also on -- line */
				assert(c==1); c=0;
				segments[segments_count++] = VG_LINE_TO;
			}
			else
			{
				/* last point was off -- quad or cubic */
				if (last_tag & 0x2)
				{
					/* cubic */
					assert(c==3); c=0;
					segments[segments_count++] = VG_CUBIC_TO;
				}
				else
				{
					/* quad */
					assert(c==2); c=0;
					segments[segments_count++] = VG_QUAD_TO;
				}
			}
		}
		else
		{
			/* off curve */
			
			if (tag & 0x2)
			{
				/* cubic */
				
				assert((last_tag & 0x1) || (last_tag & 0x2)); /* last either on or off and cubic */
			}
			else
			{
				/* quad */
				
				if (!(last_tag & 0x1))
				{
					/* last was also off curve */
					
					assert(!(last_tag & 0x2)); /* must be quad */
					
					/* add on point half-way between */
					assert(c==2); c=1;
					segments[segments_count++] = VG_QUAD_TO;
					VGfloat x = (coords[coords_count - 2] + FONT_FLOAT_FROM_26_6(points->x)) * 0.5f;
					VGfloat y = (coords[coords_count - 1] + FONT_FLOAT_FROM_26_6(points->y)) * 0.5f;
					coords[coords_count++] = x;
					coords[coords_count++] = y;
				}
			}
		}
		last_tag = tag;
		
		coords[coords_count++] = FONT_FLOAT_FROM_26_6(points->x);
		coords[coords_count++] = FONT_FLOAT_FROM_26_6(points->y);
	}
	
	if (last_tag & 0x1)
	{
		/* last point was also on -- line (implicit with close path) */
		assert(c==0);
	}
	else
	{
		++c;
		
		/* last point was off -- quad or cubic */
		if (last_tag & 0x2)
		{
			/* cubic */
			assert(c==3); c=0;
			segments[segments_count++] = VG_CUBIC_TO;
		}
		else
		{
			/* quad */
			assert(c==2); c=0;
			segments[segments_count++] = VG_QUAD_TO;
		}
		coords[coords_count++] = coords[first_coords + 0];
		coords[coords_count++] = coords[first_coords + 1];
	}
	
	segments[segments_count++] = VG_CLOSE_PATH;
}

static void convert_outline(const FT_Vector *points, const char *tags, const short *contours, short contours_count, short points_count)
{
	segments_count = 0;
	coords_count = 0;
	
	short last_contour = 0;
	for (; contours_count != 0; ++contours, --contours_count)
	{
		short contour = *contours + 1;
		convert_contour(points + last_contour, tags + last_contour, contour - last_contour);
		last_contour = contour;
	}
	assert(last_contour == points_count);
	
	assert(segments_count <= SEGMENTS_COUNT_MAX); /* oops... we overwrote some memory */
	assert(coords_count <= COORDS_COUNT_MAX);
}

int font_util_get(char *path)
{
	int i = 0;
	
	if(path == NULL || fonts == NULL)
	{
		return -1;
	}
	
	for(i = 0; i < fonts_amount; i++)
	{
		if(strcmp(fonts[i].path, path) == 0)
		{
			return i;
		}
	}
	
	return -1;
}

static FT_Face font_util_get_face(int fonts_index, char character)
{
	FT_UInt glyph_index = FT_Get_Char_Index(fonts[fonts_index].face, character);
	
	if(glyph_index == 0)
	{
		printf("Failed get character index: Unknown character code.\n");
		
		return NULL;
	}
	
	if(FT_Load_Glyph(fonts[fonts_index].face, glyph_index, FT_LOAD_NO_BITMAP | FT_LOAD_NO_HINTING | FT_LOAD_IGNORE_TRANSFORM))
	{
		printf("Failed load glyph.\n");
		
		return NULL;
	}
	
	return fonts[fonts_index].face;
}

void font_util_init(void)
{
	if(FT_Init_FreeType(&font_library))
	{
		printf("Failed to initialize freetype2. Fonts can't be used.\n");
		
		return;
	}
	
	printf("Freetype2 initialized.\n");
}

void font_util_cleanup(void)
{
	printf("Cleaning up fonts...\n");
	
	if(fonts != NULL)
	{
		while(fonts != NULL)
		{
			font_util_remove(fonts[0].path);
		}
	}
	
	FT_Done_FreeType(font_library);
}

void font_util_new(char *path)
{
	FT_Error error = 0;
	
	printf("Adding font: %s\n", path);
	
	fonts = realloc(fonts, (++fonts_amount) * sizeof(font_t));
	
	if(fonts == NULL)
	{
		printf("Failed to grow font list.\n");
		
		return;
	}
	
	fonts[fonts_amount - 1].path = strdup(path);
	
	error = FT_New_Face(font_library, path, 0, &(fonts[fonts_amount - 1].face));
	if(error == FT_Err_Unknown_File_Format)
	{
		printf("Failed to load font face: Unknown file format: %s\n", path);
		font_util_remove(path);
		
		return;
	}
	else if(error)
	{
		printf("Failed to load font face: %s (0x%x)\n", path, error);
		font_util_remove(path);
		
		return;
	}
	
	if(FT_Set_Char_Size(fonts[fonts_amount - 1].face, 0, 64 * 64, 96, 96))
	{
		printf("Failed to set font size: %s\n", path);
		font_util_remove(path);
		
		return;
	}
}

void font_util_remove(char *path)
{
	int i = 0;
	int fonts_index = 0;
	
	if(fonts == NULL)
	{
		return;
	}
	
	printf("Removing font: %s\n", path);
	
	fonts_index = font_util_get(path);
	
	if(fonts_index < 0)
	{
		printf("Failed to find font face: %s\n", path);
		
		return;
	}
	
	free(fonts[fonts_index].path);
	FT_Done_Face(fonts[fonts_index].face);
	
	for(i = fonts_index; i < fonts_amount - 1; i++)
	{
		fonts[i] = fonts[i + 1];
	}
	
	if((--fonts_amount) < 1)
	{
		free(fonts);
		fonts = NULL;
		
		return;
	}
	
	fonts = realloc(fonts, fonts_amount * sizeof(font_t));
	if(fonts == NULL)
	{
		printf("Failed to shrink font list.\n");
		
		return;
	}
}
