#ifndef _COLOR_H
#define _COLOR_H


#include <stdint.h>
#include "image.h"



__attribute__((always_inline)) inline gp_pixels_t gp_rgb_2_bgr(gp_pixels_t pixel) {

    pixel.red = pixel.red ^ pixel.blue;
    pixel.blue = pixel.blue ^ pixel.red;
    pixel.red = pixel.red ^ pixel.blue;
    return pixel;
}

#endif