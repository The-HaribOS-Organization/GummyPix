#ifndef _GRADIENT_H
#define _GRADIENT_H


#include <stdint.h>
#include <math.h>
#include "../utils.h"
#include "convolution.h"
#include "image.h"

#define DIRECTION_X 0x1
#define DIRECTION_Y 0x0


static const _Float32 sobel_x[9] = {-1.0, 0.0, 1.0, -2.0, 0.0, 2.0, -1.0, 0.0, 1.0};
static const _Float32 sobel_y[9] = {-1.0, -2.0, -1.0, 0.0, 0.0, 0.0, 1.0, 2.0, 1.0};
static const _Float32 scharr_x[9] = {3.0, 0.0, -3.0, 10.0, 0.0, -10.0, 3.0, 0.0, -3.0};
static const _Float32 scharr_y[9] = {3.0, 10.0, 3.0, 0.0, 0.0, 0.0, -3.0, -10.0, -3.0};


enum type_gradient {
    SOBEL_GRADIENT,
    SCHARR_GRADIENT
};

_Float32 *gp_gradient(const gp_image_t *image, enum type_gradient type, uint8_t direction);

__attribute__((always_inline)) inline _Float32 gp_gradient_phase(gp_point_t point) {

    return (atan2f(point.y, point.x));
}

#endif
