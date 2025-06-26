#ifndef _BOOLEAN_H
#define _BOOLEAN_H


#include <stdint.h>
#include "image.h"


#define NOT(pixel) ({ \
    return (gp_pixels_t){~pixel.red, pixel.green, pixel.blue, 0}; \
})



gp_pixels_t gp_and(gp_image_t *image);
gp_pixels_t gp_or(gp_image_t *image);
gp_pixels_t gp_xor(gp_image_t *image);
gp_pixels_t gp_not(gp_image_t *image);

#endif
