/*
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
static char *font_version = NULL;

// freetype errors
#undef __FTERRORS_H__
#define FT_ERRORDEF( e, v, s )  { e, s },
#define FT_ERROR_START_LIST     {
#define FT_ERROR_END_LIST       { 0, 0 } };

typedef struct font_errors_t
{
	int err_code;
	const char* err_msg;
} font_errors_t;

font_errors_t font_errors[] =

#include FT_ERRORS_H

/**
 * Converts a FreeType error to an error message (as string).
 * @param error The error code.
 * @return The corresponding error message (as string). Returns "unknown error"
 *         if the given error code is not a valid error code.
 */
static const char *font_util_get_error(int error)
{
	font_errors_t *font_errors_pointer = font_errors;
	
	while((*font_errors_pointer).err_msg)
	{
		if((*font_errors_pointer).err_code == error)
		{
			return (*font_errors_pointer).err_msg;
		}
		
		font_errors_pointer++;
	}
	
	return "unknown error";
}

/**
 * Returns the font index used internally.
 * @param name The name of the font. This is the name of the font at
 *             initialization with "int font_util_new(char *path, char *name)".
 * @return The found font index. If no font matches with the given name -1 will
 *         be returned.
 */
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

/**
 * Returns the font name of a given font index.
 * @param fonts_index The font index.
 * @return The font name as string. If no fonts are available an empty string is
 *         returned.
 */
char *font_util_get_name(unsigned int fonts_index)
{
	if(fonts == NULL)
	{
		return "";
	}
	
	return fonts[fonts_index].name;
}

/**
 * Initializes font usage by initializing the freetype library. In addition this
 * function retrieves the freetype version and stores it for later usage. The
 * version consists of a string which will be freed at font cleanup.
 * @return The success value which is 0 when everything is initialized or -1
 *         when an error has occurred.
 */
int font_util_init(void)
{
	FT_Int major = 0;
	FT_Int minor = 0;
	FT_Int patch = 0;
	int error = 0;
	
	printf("Error: %s\n", font_util_get_error(FT_Err_Unknown_File_Format));
	
	error = FT_Init_FreeType(&font_library);
	if(error != 0)
	{
		eprintf("Failed to initialize FreeType. Fonts can't be used: %s\n", font_util_get_error(error));
		
		font_library = NULL;
		
		return -1;
	}
	
	FT_Library_Version(font_library, &major, &minor, &patch);
	
	font_version = malloc(((major == 0 ? 1 : (int)(log10(major)+1)) + 1 + (minor == 0 ? 1 : (int)(log10(minor)+1)) + 1 + (patch == 0 ? 1 : (int)(log10(patch)+1))) * sizeof(char) + 1);
	if(font_version == NULL)
	{
		eprintf("Failed to initialize version.\n");
		
		// errno set by malloc
		
		return -1;
	}
	
	sprintf(font_version, "%i.%i.%i", major, minor, patch);
	
	return 0;
}

/**
 * Returns the freetype version string. This string is available if the font
 * utils are initialized and not cleaned up.
 * @return The version string.
 */
char *font_util_version(void)
{
	return font_version;
}

/**
 * Cleans up all fonts and the font library. In addition the freetype version
 * string is also freed.
 */
void font_util_cleanup(void)
{
	if(fonts != NULL)
	{
		while(fonts != NULL)
		{
			font_util_remove(fonts[0].name);
		}
	}
	
	if(font_library != NULL)
	{
		FT_Done_FreeType(font_library);
	}
	
	free(font_version);
}

/**
 * Callback function for the outline path decomposing. This function handles a
 * translation.
 */
static int font_util_outline_decompose_move_to(const FT_Vector *to, void *user)
{
	VGubyte segment[1] = { VG_MOVE_TO_ABS };
	VGfloat data[2];
	
	data[0] = FONT_UTIL_TO_FLOAT(to->x);
	data[1] = FONT_UTIL_TO_FLOAT(to->y);
	
	vgAppendPathData(*(VGPath *)user, 1, segment, (const void *)data);
	
	point_count += 2;
	
	return 0;
}

/**
 * Callback function for the outline path decomposing. This function handles a
 * line.
 */
static int font_util_outline_decompose_line_to(const FT_Vector *to, void *user)
{
	VGubyte segment[1] = { VG_LINE_TO_ABS };
	VGfloat data[2];
	
	data[0] = FONT_UTIL_TO_FLOAT(to->x);
	data[1] = FONT_UTIL_TO_FLOAT(to->y);
	
	vgAppendPathData(*(VGPath *)user, 1, segment, (const void *)data);
	
	point_count += 2;
	
	return 0;
}

/**
 * Callback function for the outline path decomposing. This function handles a
 * quadratic curve.
 */
static int font_util_outline_decompose_conic_to(const FT_Vector *control, const FT_Vector *to, void *user)
{
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


/**
 * Callback function for the outline path decomposing. This function handles a
 * bezier curve.
 */
static int font_util_outline_decompose_cubic_to(const FT_Vector *control1, const FT_Vector *control2, const FT_Vector *to, void *user)
{
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


/**
 * Callback function for the outline path decomposing. This function handles a
 * close path operation.
 */
static void font_util_outline_decompose_close_path(void *user)
{
	VGubyte segment[1] = { VG_CLOSE_PATH };
	VGfloat data[2];
	
	data[0] = 0;
	data[1] = 0;
	
	vgAppendPathData(*(VGPath *)user, 1, segment, (const void *)data);
}

/**
 * Registers a new font in the font list. This function initializes a given font
 * file, processes/converts all important informations and stores the data in
 * the VRAM or the font list.
 * @param path The path of a valid font file. (e.g. TrueType-file)
 * @param name The font name. Fonts in the font list are identified by this font
 *             name.
 * @return Returns 0 on success, else it returns -1. On error sometimes an
 *         errno is set or a error message is printed on log output.
 */
int font_util_new(char *path, char *name)
{
	int i = 0;
	FT_Error error = 0;
	FT_Outline_Funcs outline_functions;
	FT_ULong charcode;
	FT_UInt gindex;
	VGPath glyph_path = 0;
	
	outline_functions.move_to = &font_util_outline_decompose_move_to;
	outline_functions.line_to = &font_util_outline_decompose_line_to;
	outline_functions.conic_to = &font_util_outline_decompose_conic_to;
	outline_functions.cubic_to = &font_util_outline_decompose_cubic_to;
	
	outline_functions.shift = 0;
	outline_functions.delta = 0;
	
	if(font_library == NULL)
	{
		return -1;
	}
	
	fonts = realloc(fonts, (++fonts_amount) * sizeof(font_t));
	
	if(fonts == NULL)
	{
		eprintf("%s: Failed to grow font list.\n", name);
		
		// errno set by realloc
		
		return -1;
	}
	
	fonts[fonts_amount - 1].path = strdup(path);
	fonts[fonts_amount - 1].name = strdup(name);
	
	// read font file
	error = FT_New_Face(font_library, path, 0, &(fonts[fonts_amount - 1].face));
	if(error != 0)
	{
		eprintf("%s: Failed to load font face: %s\n", name, font_util_get_error(error));
		
		fonts[fonts_amount - 1].face = NULL;
		font_util_remove(name);
		
		errno = EBFONT; // Bad font file format
		
		return -1;
	}
	
	// set character size
	error = FT_Set_Char_Size(fonts[fonts_amount - 1].face, 0, FONT_UTIL_SIZE, 96, 96);
	if(error != 0)
	{
		eprintf("%s: Failed to set font size (char): %s\n", name, font_util_get_error(error));
		
		font_util_remove(name);
		
		return -1;
	}
	
	char_count = 0;
	
	// count characters to allocate the character array
	charcode = FT_Get_First_Char(fonts[fonts_amount - 1].face, &gindex);
	while(gindex != 0)
	{
		charcode = FT_Get_Next_Char(fonts[fonts_amount - 1].face, charcode, &gindex);
		
		char_count++;
	}
	
	fonts[fonts_amount - 1].characters = malloc(char_count * sizeof(character_t *));
	fonts[fonts_amount - 1].characters_amount = char_count;
	if(fonts[fonts_amount - 1].characters == NULL)
	{
		eprintf("%s: Failed to allocate character array\n", name);
		
		font_util_remove(name);
		
		// errno set by malloc
		
		return -1;
	}
	
	// allocate characters
	for(i = 0; i < fonts[fonts_amount - 1].characters_amount; i++)
	{
		fonts[fonts_amount - 1].characters[i] = malloc(sizeof(character_t));
		if(fonts[fonts_amount - 1].characters[i] == NULL)
		{
			eprintf("%s: Failed to allocate glyph\n", name);
			
			font_util_remove(name);
			
			// errno set by malloc
			
			return -1;
		}
	}
	
	// retrieve character informations
	fonts[fonts_amount - 1].ascender = 0;
	fonts[fonts_amount - 1].descender = 0;
	char_count = 0;
	point_count = 0;
	charcode = FT_Get_First_Char(fonts[fonts_amount - 1].face, &gindex);
	while(gindex != 0)
	{
		error = FT_Load_Glyph(fonts[fonts_amount - 1].face, gindex, FT_LOAD_NO_BITMAP | FT_LOAD_NO_HINTING | FT_LOAD_IGNORE_TRANSFORM);
		if(error != 0)
		{
			eprintf("%s: Failed load glyph: %s\n", name, font_util_get_error(error));
			
			continue;
		}
		
		// generate outline path and store it into a VGPath
		glyph_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
		error = FT_Outline_Decompose(&(fonts[fonts_amount - 1].face->glyph->outline), &outline_functions, (void *)(&glyph_path));
		if(error != 0)
		{
			eprintf("%s: Failed to decompose glyph outline: %s\n", name, font_util_get_error(error));
			
			vgDestroyPath(glyph_path);
			
			continue;
		}
		font_util_outline_decompose_close_path((void *)(&glyph_path));
		
		// save character informations
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
	
	// save kerning availability
	if(FT_HAS_KERNING(fonts[fonts_amount - 1].face))
	{
		fonts[fonts_amount - 1].kerning_available = VG_TRUE;
	}
	else
	{
		fonts[fonts_amount - 1].kerning_available = VG_FALSE;
	}
	
	return 0;
}

/**
 * Removes a registered font from the font list.
 * @param name The name of the font.
 * @return Returns 0 on success, else it returns -1. On error sometimes an
 *          errno is set or a error message is printed on log output.
 */
int font_util_remove(char *name)
{
	int i = 0;
	int fonts_index = 0;
	
	if(fonts == NULL)
	{
		return -1;
	}
	
	fonts_index = font_util_get(name);
	
	if(fonts_index < 0)
	{
		eprintf("Failed to find font face: %s\n", name);
		
		return -1;
	}
	
	free(fonts[fonts_index].path);
	free(fonts[fonts_index].name);
	
	if(fonts[fonts_index].face)
	{
		FT_Done_Face(fonts[fonts_index].face);
		
		// free characters
		for(i = 0; i < fonts[fonts_index].characters_amount; i++)
		{
			vgDestroyPath(fonts[fonts_index].characters[i]->path);
			free(fonts[fonts_index].characters[i]);
		}
		free(fonts[fonts_index].characters);
	}
	
	// realign font list
	for(i = fonts_index; i < fonts_amount - 1; i++)
	{
		fonts[i] = fonts[i + 1];
	}
	
	if((--fonts_amount) < 1)
	{
		// font list is empty
		free(fonts);
		fonts = NULL;
		
		return 0;
	}
	
	// reallocate font list to the correct
	fonts = realloc(fonts, fonts_amount * sizeof(font_t));
	if(fonts == NULL)
	{
		eprintf("Failed to shrink font list.\n");
		
		// errno set by realloc
		
		return -1;
	}
	
	return 0;
}

/**
 * Returns the character index of a font.
 * @param fonts_index The font index of a font.
 * @param character The searched character.
 * @return The character index or -1 if the character could not be found.
 */
int font_util_get_char_index(unsigned int fonts_index, char character)
{
	int i = 0;
	
	if(fonts == NULL)
	{
		return -1;
	}
	
	// loop through characters
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

/**
 * Returns the character path of a character of a font.
 * @param fonts_index The font index of a font.
 * @param char_index The character index of a character.
 * @return The path of the given character and font.
 */
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

/**
 * Returns the character width of a character of a font.
 * @param fonts_index The font index of a font.
 * @param char_index The character index of a character.
 * @return The width of the given character and font.
 */
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

/**
 * Returns the character height of a character of a font.
 * @param fonts_index The font index of a font.
 * @param char_index The character index of a character.
 * @return The height of the given character and font.
 */
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

/**
 * Returns the character advance of the x axis of a character of a font.
 * @param fonts_index The font index of a font.
 * @param char_index The character index of a character.
 * @return The advance of the x axis of the given character and font.
 */
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

/**
 * Returns the character advance of the y axis of a character of a font.
 * @param fonts_index The font index of a font.
 * @param char_index The character index of a character.
 * @return The advance of the y axis of the given character and font.
 */
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

/**
 * Returns the character bearing of the y axis of a character of a font.
 * @param fonts_index The font index of a font.
 * @param char_index The character index of a character.
 * @return The bearing of the y axis of the given character and font.
 */
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

/**
 * Returns if the given font supports kerning.
 * @param fonts_index The font index of a font.
 * @return VG_TRUE if the font supports kerning, else VG_FALSE is returned.
 */
VGboolean font_util_get_kerning_availability(unsigned int fonts_index)
{
	if(fonts == NULL)
	{
		return VG_FALSE;
	}
	
	return fonts[fonts_index].kerning_available;
}

/**
 * Returns character kerning of a given pair of characters.
 * @param fonts_index The font index of a font.
 * @param character The current character.
 * @param character_next The next character.
 * @return The kerning translation of the two characters.
 */
VGfloat font_util_get_kerning_x(unsigned int fonts_index, char character, char character_next)
{
	int char_index = 0;
	int char_index_next = 0;
	FT_Vector kerning = { 0, 0 };
	
	if(font_library == NULL || fonts == NULL)
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

/**
 * Returns the ascender of a font.
 * @param fonts_index The font index of a font.
 * @return The ascender of a font.
 */
VGfloat font_util_get_ascender(unsigned int fonts_index)
{
	if(fonts == NULL)
	{
		return 0;
	}
	
	return fonts[fonts_index].ascender;
}

/**
 * Returns the descender of a font.
 * @param fonts_index The font index of a font.
 * @return The descender of a font.
 */
VGfloat font_util_get_descender(unsigned int fonts_index)
{
	if(fonts == NULL)
	{
		return 0;
	}
	
	return fonts[fonts_index].descender;
}
