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

#include "log-util.h"
#include "font-util.h"

static unsigned long long int point_count = 0;
static unsigned int char_count = 0;

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

// static void convert_contour(const FT_Vector *points, const char *tags, short points_count)
// {
// 	int first_coords = coords_count;
	
// 	int first = 1;
// 	char last_tag = 0;
// 	int c = 0;
	
// 	for (; points_count != 0; ++points, ++tags, --points_count)
// 	{
// 		++c;
		
// 		char tag = *tags;
// 		if(first)
// 		{
// 			assert(tag & 0x1);
// 			assert(c==1); c=0;
// 			segments[segments_count++] = VG_MOVE_TO;
// 			first = 0;
// 		}
// 		else if(tag & 0x1)
// 		{
// 			/* on curve */
			
// 			if (last_tag & 0x1)
// 			{
// 				/* last point was also on -- line */
// 				assert(c==1); c=0;
// 				segments[segments_count++] = VG_LINE_TO;
// 			}
// 			else
// 			{
// 				/* last point was off -- quad or cubic */
// 				if (last_tag & 0x2)
// 				{
// 					/* cubic */
// 					assert(c==3); c=0;
// 					segments[segments_count++] = VG_CUBIC_TO;
// 				}
// 				else
// 				{
// 					/* quad */
// 					assert(c==2); c=0;
// 					segments[segments_count++] = VG_QUAD_TO;
// 				}
// 			}
// 		}
// 		else
// 		{
// 			/* off curve */
			
// 			if (tag & 0x2)
// 			{
// 				/* cubic */
				
// 				assert((last_tag & 0x1) || (last_tag & 0x2)); /* last either on or off and cubic */
// 			}
// 			else
// 			{
// 				/* quad */
				
// 				if (!(last_tag & 0x1))
// 				{
// 					/* last was also off curve */
					
// 					assert(!(last_tag & 0x2)); /* must be quad */
					
// 					/* add on point half-way between */
// 					assert(c==2); c=1;
// 					segments[segments_count++] = VG_QUAD_TO;
// 					VGfloat x = (coords[coords_count - 2] + FONT_FLOAT_FROM_26_6(points->x)) * 0.5f;
// 					VGfloat y = (coords[coords_count - 1] + FONT_FLOAT_FROM_26_6(points->y)) * 0.5f;
// 					coords[coords_count++] = x;
// 					coords[coords_count++] = y;
// 				}
// 			}
// 		}
// 		last_tag = tag;
		
// 		coords[coords_count++] = FONT_FLOAT_FROM_26_6(points->x);
// 		coords[coords_count++] = FONT_FLOAT_FROM_26_6(points->y);
// 	}
	
// 	if (last_tag & 0x1)
// 	{
// 		/* last point was also on -- line (implicit with close path) */
// 		assert(c==0);
// 	}
// 	else
// 	{
// 		++c;
		
// 		/* last point was off -- quad or cubic */
// 		if (last_tag & 0x2)
// 		{
// 			/* cubic */
// 			assert(c==3); c=0;
// 			segments[segments_count++] = VG_CUBIC_TO;
// 		}
// 		else
// 		{
// 			/* quad */
// 			assert(c==2); c=0;
// 			segments[segments_count++] = VG_QUAD_TO;
// 		}
// 		coords[coords_count++] = coords[first_coords + 0];
// 		coords[coords_count++] = coords[first_coords + 1];
// 	}
	
// 	segments[segments_count++] = VG_CLOSE_PATH;
// }

// void convert_outline(const FT_Vector *points, const char *tags, const short *contours, short contours_count, short points_count)
// {
// 	segments_count = 0;
// 	coords_count = 0;
	
// 	short last_contour = 0;
// 	for (; contours_count != 0; ++contours, --contours_count)
// 	{
// 		short contour = *contours + 1;
// 		convert_contour(points + last_contour, tags + last_contour, contour - last_contour);
// 		last_contour = contour;
// 	}
// 	assert(last_contour == points_count);
	
// 	assert(segments_count <= SEGMENTS_COUNT_MAX); /* oops... we overwrote some memory */
// 	assert(coords_count <= COORDS_COUNT_MAX);
// }

int font_util_get(char *name)
{
	int i = 0;
	
	if(name == NULL || fonts == NULL)
	{
		return -1;
	}
	
	for(i = 0; i < fonts_amount; i++)
	{
		if(strcmp(fonts[i].name, name) == 0)
		{
			return i;
		}
	}
	
	return -1;
}

FT_Face font_util_get_face(int fonts_index, char character)
{
	FT_UInt glyph_index = FT_Get_Char_Index(fonts[fonts_index].face, character);
	
	if(glyph_index == 0)
	{
		eprintf("Failed get character index: Unknown character code.\n");
		
		return NULL;
	}
	
	if(FT_Load_Glyph(fonts[fonts_index].face, glyph_index, FT_LOAD_NO_BITMAP | FT_LOAD_NO_HINTING | FT_LOAD_IGNORE_TRANSFORM))
	{
		eprintf("Failed load glyph.\n");
		
		return NULL;
	}
	
	return fonts[fonts_index].face;
}

VGFont font_util_get_font(int fonts_index)
{
	return fonts[fonts_index].vg_font;
}

void font_util_init(void)
{
	FT_Int major = 0;
	FT_Int minor = 0;
	FT_Int patch = 0;
	
	if(FT_Init_FreeType(&font_library))
	{
		eprintf("Failed to initialize freetype2. Fonts can't be used.\n");
		
		return;
	}
	
	FT_Library_Version(font_library, &major, &minor, &patch);
	
	printf("Freetype %i.%i.%i initialized.\n", major, minor, patch);
}

void font_util_cleanup(void)
{
	printf("Cleaning up fonts...\n");
	
	if(fonts != NULL)
	{
		while(fonts != NULL)
		{
			font_util_remove(fonts[0].name);
		}
	}
	
	FT_Done_FreeType(font_library);
}

static int font_util_outline_decode_move_to(const FT_Vector *to, void *user)
{
	// printf("moveTo(%f, %f)\n", FONT_UTIL_TO_FLOAT(to->x), FONT_UTIL_TO_FLOAT(to->y));
	
	VGubyte segment[1] = { VG_MOVE_TO_ABS };
	VGfloat data[2];
	
	data[0] = FONT_UTIL_TO_FLOAT(to->x);
	data[1] = FONT_UTIL_TO_FLOAT(to->y);
	
	vgAppendPathData(*(VGPath *)user, 1, segment, (const void *)data);
	
	point_count += 2;
	
	return 0;
}

static int font_util_outline_decode_line_to(const FT_Vector *to, void *user)
{
	// printf("lineTo(%f, %f)\n", FONT_UTIL_TO_FLOAT(to->x), FONT_UTIL_TO_FLOAT(to->y));
	
	VGubyte segment[1] = { VG_LINE_TO_ABS };
	VGfloat data[2];
	
	data[0] = FONT_UTIL_TO_FLOAT(to->x);
	data[1] = FONT_UTIL_TO_FLOAT(to->y);
	
	vgAppendPathData(*(VGPath *)user, 1, segment, (const void *)data);
	
	point_count += 2;
	
	return 0;
}

static int font_util_outline_decode_conic_to(const FT_Vector *control, const FT_Vector *to, void *user)
{
	// printf("conicTo(%f, %f, %f, %f)\n", FONT_UTIL_TO_FLOAT(control->x), FONT_UTIL_TO_FLOAT(control->y), FONT_UTIL_TO_FLOAT(to->x), FONT_UTIL_TO_FLOAT(to->y));
	
	VGubyte segment[1] = { VG_QUAD_TO_ABS };
	VGfloat data[4];
	
	data[0] = FONT_UTIL_TO_FLOAT(control->x);
	data[1] = FONT_UTIL_TO_FLOAT(control->y);
	data[2] = FONT_UTIL_TO_FLOAT(to->x);
	data[3] = FONT_UTIL_TO_FLOAT(to->y);
	
	vgAppendPathData(*(VGPath *)user, 1, segment, (const void *)data);
	
	point_count += 4;
	
	return 0;
}

static int font_util_outline_decode_cubic_to(const FT_Vector *control1, const FT_Vector *control2, const FT_Vector *to, void *user)
{
	// printf("cubicTo(%f, %f, %f, %f, %f, %f)\n", FONT_UTIL_TO_FLOAT(control1->x), FONT_UTIL_TO_FLOAT(control1->y), FONT_UTIL_TO_FLOAT(control2->x), FONT_UTIL_TO_FLOAT(control2->y), FONT_UTIL_TO_FLOAT(to->x), FONT_UTIL_TO_FLOAT(to->y));
	
	VGubyte segment[1] = { VG_CUBIC_TO_ABS };
	VGfloat data[6];
	
	data[0] = FONT_UTIL_TO_FLOAT(control1->x);
	data[1] = FONT_UTIL_TO_FLOAT(control1->y);
	data[2] = FONT_UTIL_TO_FLOAT(control2->x);
	data[3] = FONT_UTIL_TO_FLOAT(control2->y);
	data[4] = FONT_UTIL_TO_FLOAT(to->x);
	data[5] = FONT_UTIL_TO_FLOAT(to->y);
	
	vgAppendPathData(*(VGPath *)user, 1, segment, (const void *)data);
	
	point_count += 6;
	
	return 0;
}

int font_util_new(char *path, char *name)
{
	FT_Error error = 0;
	FT_Outline_Funcs outline_functions;
	FT_ULong charcode;
	FT_UInt gindex;
	VGPath glyph_path = 0;
	VGfloat glyph_origin[2] = { 0, 0 };
	VGfloat glyph_escapement[2] = { 0, 0 };
	
	outline_functions.move_to = &font_util_outline_decode_move_to;
	outline_functions.line_to = &font_util_outline_decode_line_to;
	outline_functions.conic_to = &font_util_outline_decode_conic_to;
	outline_functions.cubic_to = &font_util_outline_decode_cubic_to;
	
	outline_functions.shift = 0;
	outline_functions.delta = 0;
	
	printf("Adding font: %s, name: %s\n", path, name);
	
	fonts = realloc(fonts, (++fonts_amount) * sizeof(font_t));
	
	if(fonts == NULL)
	{
		eprintf("Failed to grow font list.\n");
		
		return -1;
	}
	
	fonts[fonts_amount - 1].path = strdup(path);
	fonts[fonts_amount - 1].name = strdup(name);
	
	error = FT_New_Face(font_library, path, 0, &(fonts[fonts_amount - 1].face));
	if(error == FT_Err_Unknown_File_Format)
	{
		eprintf("Failed to load font face: Unknown file format: %s\n", name);
		font_util_remove(name);
		
		return -1;
	}
	else if(error)
	{
		eprintf("Failed to load font face: %s (0x%x)\n", name, error);
		font_util_remove(name);
		
		return -1;
	}
	
	if(FT_Set_Char_Size(fonts[fonts_amount - 1].face, 0, FONT_UTIL_SIZE, 96, 96))
	{
		eprintf("Failed to set font size: %s\n", name);
		font_util_remove(name);
		
		return -1;
	}
	
	printf("Converting characters...\n");
	fonts[fonts_amount - 1].vg_font = vgCreateFont(0);
	
	charcode = FT_Get_First_Char(fonts[fonts_amount - 1].face, &gindex);
	while(gindex != 0)
	{
		if(FT_Load_Glyph(fonts[fonts_amount - 1].face, gindex, FT_LOAD_NO_BITMAP | FT_LOAD_NO_HINTING | FT_LOAD_IGNORE_TRANSFORM))
		{
			eprintf("Failed load glyph.\n");
			vgDestroyPath(glyph_path);
			font_util_remove(name);
			
			return -1;
		}
		
		glyph_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
		
		error = FT_Outline_Decompose(&(fonts[fonts_amount - 1].face->glyph->outline), &outline_functions, (void *)(&glyph_path));
		if(error != 0)
		{
			eprintf("Failed to decompose glyph outline: %s\n", name);
			vgDestroyPath(glyph_path);
			font_util_remove(name);
			
			return -1;
		}
		
		glyph_escapement[0] = FONT_UTIL_TO_FLOAT(fonts[fonts_amount - 1].face->glyph->metrics.horiAdvance);
		glyph_escapement[1] = 0; // horizontal text
		
		// printf("%4i: Storing %i segments and %i coordinates...\n", char_count, vgGetParameteri(glyph_path, VG_PATH_NUM_SEGMENTS), vgGetParameteri(glyph_path, VG_PATH_NUM_COORDS));
		
		vgSetGlyphToPath(fonts[fonts_amount - 1].vg_font, charcode, glyph_path, VG_FALSE, glyph_origin, glyph_escapement);
		
		vgDestroyPath(glyph_path);
		
		charcode = FT_Get_Next_Char(fonts[fonts_amount - 1].face, charcode, &gindex);
		
		char_count++;
	}
	
	printf("%i characters, %lli coordinates\n", vgGetParameteri(fonts[fonts_amount - 1].vg_font, VG_FONT_NUM_GLYPHS), point_count);
	
	return 0;
}

void font_util_remove(char *name)
{
	int i = 0;
	int fonts_index = 0;
	
	if(fonts == NULL)
	{
		return;
	}
	
	printf("Removing font: %s\n", name);
	
	fonts_index = font_util_get(name);
	
	if(fonts_index < 0)
	{
		eprintf("Failed to find font face: %s\n", name);
		
		return;
	}
	
	free(fonts[fonts_index].path);
	free(fonts[fonts_index].name);
	FT_Done_Face(fonts[fonts_index].face);
	vgDestroyFont(fonts[fonts_index].vg_font);
	
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
		eprintf("Failed to shrink font list.\n");
		
		return;
	}
}

VGuint segments_count_get(void)
{
	return segments_count;
}

VGubyte *segments_get(void)
{
	return segments;
}

VGuint coords_count_get(void)
{
	return coords_count;
}

VGfloat *coords_get(void)
{
	return coords;
}
