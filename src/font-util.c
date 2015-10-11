/**
 * Copyright (C) 2015 NIPE-SYSTEMS
 * Copyright (C) 2015 Hauke Oldsen
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

FT_Face font_util_get_face(unsigned int fonts_index, char character)
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
	int i = 0;
	FT_Error error = 0;
	FT_Outline_Funcs outline_functions;
	FT_ULong charcode;
	FT_UInt gindex;
	VGPath glyph_path = 0;
	
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
		eprintf("Failed to set font size (char): %s\n", name);
		font_util_remove(name);
		
		return -1;
	}
	
	printf("Counting characters...\n");
	char_count = 0;
	
	charcode = FT_Get_First_Char(fonts[fonts_amount - 1].face, &gindex);
	while(gindex != 0)
	{
		charcode = FT_Get_Next_Char(fonts[fonts_amount - 1].face, charcode, &gindex);
		
		char_count++;
	}
	
	printf("%i characters\n", char_count);
	
	printf("Converting characters...\n");
	fonts[fonts_amount - 1].characters = malloc(char_count * sizeof(character_t *));
	fonts[fonts_amount - 1].characters_amount = char_count;
	if(fonts[fonts_amount - 1].characters == NULL)
	{
		eprintf("Failed to allocate character array: %s\n", name);
		font_util_remove(name);
		
		return -1;
	}
	
	for(i = 0; i < fonts[fonts_amount - 1].characters_amount; i++)
	{
		fonts[fonts_amount - 1].characters[i] = malloc(sizeof(character_t));
		if(fonts[fonts_amount - 1].characters[i] == NULL)
		{
			eprintf("Failed to allocate glyph: %s\n", name);
			font_util_remove(name);
			
			return -1;
		}
	}
	
	fonts[fonts_amount - 1].ascender = 0;
	fonts[fonts_amount - 1].descender = 0;
	char_count = 0;
	point_count = 0;
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
		
		fonts[fonts_amount - 1].characters[char_count]->charcode = charcode;
		fonts[fonts_amount - 1].characters[char_count]->glyph_index = gindex;
		fonts[fonts_amount - 1].characters[char_count]->path = glyph_path;
		fonts[fonts_amount - 1].characters[char_count]->width = FONT_UTIL_TO_FLOAT(fonts[fonts_amount - 1].face->glyph->metrics.width);
		fonts[fonts_amount - 1].characters[char_count]->height = FONT_UTIL_TO_FLOAT(fonts[fonts_amount - 1].face->glyph->metrics.height);
		fonts[fonts_amount - 1].characters[char_count]->advance_x = FONT_UTIL_TO_FLOAT(fonts[fonts_amount - 1].face->glyph->metrics.horiAdvance);
		fonts[fonts_amount - 1].characters[char_count]->bearing_x = FONT_UTIL_TO_FLOAT(fonts[fonts_amount - 1].face->glyph->metrics.horiBearingX);
		fonts[fonts_amount - 1].characters[char_count]->bearing_y = FONT_UTIL_TO_FLOAT(fonts[fonts_amount - 1].face->glyph->metrics.horiBearingY);
		
		if(fonts[fonts_amount - 1].characters[char_count]->bearing_y > fonts[fonts_amount - 1].ascender)
		{
			fonts[fonts_amount - 1].ascender = fonts[fonts_amount - 1].characters[char_count]->bearing_y;
		}
		
		if(fonts[fonts_amount - 1].characters[char_count]->height - fonts[fonts_amount - 1].characters[char_count]->bearing_y > fonts[fonts_amount - 1].descender)
		{
			fonts[fonts_amount - 1].descender = fonts[fonts_amount - 1].characters[char_count]->height - fonts[fonts_amount - 1].characters[char_count]->bearing_y;
		}
		
		charcode = FT_Get_Next_Char(fonts[fonts_amount - 1].face, charcode, &gindex);
		
		char_count++;
	}
	
	printf("%i converted characters, %lli coordinates\n", char_count, point_count);
	
	if(FT_HAS_KERNING(fonts[fonts_amount - 1].face))
	{
		printf("Kerning for font '%s' available.\n", name);
		
		fonts[fonts_amount - 1].kerning_available = VG_TRUE;
	}
	else
	{
		fonts[fonts_amount - 1].kerning_available = VG_FALSE;
	}
	
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
	
	for(i = 0; i < fonts[fonts_index].characters_amount; i++)
	{
		vgDestroyPath(fonts[fonts_index].characters[i]->path);
		free(fonts[fonts_index].characters[i]);
	}
	free(fonts[fonts_index].characters);
	
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

int font_util_get_char_index(unsigned int fonts_index, char character)
{
	int i = 0;
	
	if(fonts == NULL)
	{
		return -1;
	}
	
	for(i = 0; i < fonts[fonts_index].characters_amount; i++)
	{
		if(fonts[fonts_index].characters[i]->charcode == character)
		{
			return i;
		}
	}
	
	eprintf("Failed to find character.\n");
	
	return -1;
}

VGPath font_util_get_path(unsigned int fonts_index, int char_index)
{
	if(fonts == NULL)
	{
		return VG_INVALID_HANDLE;
	}
	
	if(char_index != -1)
	{
		return fonts[fonts_index].characters[char_index]->path;
	}
	
	return VG_INVALID_HANDLE;
}

VGfloat font_util_get_width(unsigned int fonts_index, int char_index)
{
	if(fonts == NULL)
	{
		return 0;
	}
	
	if(char_index != -1)
	{
		return fonts[fonts_index].characters[char_index]->width;
	}
	
	return 0;
}

VGfloat font_util_get_height(unsigned int fonts_index, int char_index)
{
	if(fonts == NULL)
	{
		return 0;
	}
	
	if(char_index != -1)
	{
		return fonts[fonts_index].characters[char_index]->height;
	}
	
	return 0;
}

VGfloat font_util_get_advance_x(unsigned int fonts_index, int char_index)
{
	if(fonts == NULL)
	{
		return 0;
	}
	
	if(char_index != -1)
	{
		return fonts[fonts_index].characters[char_index]->advance_x;
	}
	
	return 0;
}

VGfloat font_util_get_bearing_x(unsigned int fonts_index, int char_index)
{
	if(fonts == NULL)
	{
		return 0;
	}
	
	if(char_index != -1)
	{
		return fonts[fonts_index].characters[char_index]->bearing_x;
	}
	
	return 0;
}

VGfloat font_util_get_bearing_y(unsigned int fonts_index, int char_index)
{
	if(fonts == NULL)
	{
		return 0;
	}
	
	if(char_index != -1)
	{
		return fonts[fonts_index].characters[char_index]->bearing_y;
	}
	
	return 0;
}

VGboolean font_util_get_kerning_availability(unsigned int fonts_index)
{
	if(fonts == NULL)
	{
		return VG_FALSE;
	}
	
	return fonts[fonts_index].kerning_available;
}

VGfloat font_util_get_kerning_x(unsigned int fonts_index, char character, char character_next)
{
	int char_index = 0;
	int char_index_next = 0;
	FT_Vector kerning = { 0, 0 };
	
	if(fonts == NULL)
	{
		return 0;
	}
	
	char_index = font_util_get_char_index(fonts_index, character);
	char_index_next = font_util_get_char_index(fonts_index, character_next);
	
	if(char_index == -1)
	{
		eprintf("Failed to find glyph for kerning.\n");
		
		return 0;
	}
	
	if(char_index_next == -1)
	{
		eprintf("Failed to find next glyph for kerning.\n");
		
		return 0;
	}
	
	FT_Get_Kerning(fonts[fonts_index].face, fonts[fonts_index].characters[char_index]->glyph_index, fonts[fonts_index].characters[char_index_next]->glyph_index, FT_KERNING_DEFAULT, &kerning);
	
	return FONT_UTIL_TO_FLOAT(kerning.x);
}

VGfloat font_util_get_ascender(unsigned int fonts_index)
{
	if(fonts == NULL)
	{
		return 0;
	}
	
	return fonts[fonts_index].ascender;
}

VGfloat font_util_get_descender(unsigned int fonts_index)
{
	if(fonts == NULL)
	{
		return 0;
	}
	
	return fonts[fonts_index].descender;
}
