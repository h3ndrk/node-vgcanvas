#ifndef __IMAGE_UTIL_H__
#define __IMAGE_UTIL_H__

#include "include-openvg.h"

typedef struct image_t {
  VGImage image;
  VGuint width, height;
} image_t;

image_t *image_load(char *path);
void image_cleanup(image_t *image);

#endif
