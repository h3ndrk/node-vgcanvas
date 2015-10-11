#include "egl-util.h"
#include "include-openvg.h"
#include "image-util.h"

void canvas_drawImage(image_t *image, VGfloat dx, VGfloat dy, VGfloat dw, VGfloat dh, VGfloat sx, VGfloat sy, VGfloat sw, VGfloat sh)
{
  VGint matrix = vgGeti(VG_MATRIX_MODE);
  vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
  
  vgLoadIdentity();
  vgTranslate(dx, egl_get_height() - dy - dh);
  vgScale(dw / sw, dh / sh);
  
  VGImage child = vgChildImage(image->image, sx, image->height - sy - sh, sw, sh);
  vgDrawImage(child);
  vgDestroyImage(child);
  
  vgSeti(VG_MATRIX_MODE, matrix);
}
