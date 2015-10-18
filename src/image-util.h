#ifndef __IMAGE_UTIL_H__
#define __IMAGE_UTIL_H__

#include "include-openvg.h"
#include <FreeImage.h>

typedef struct image_t {
  VGImage image;
  VGuint width, height;
} image_t;

image_t *image_load(const char *path);
FIBITMAP* image_load_bitmap(const char *path);
image_t* image_create(FIBITMAP *bitmap);
void image_cleanup(image_t *image);
void image_free_bitmap(FIBITMAP *bitmap);
char *image_to_data_url(char *type, float encoder_options, size_t *data_base64_amount);

#endif
