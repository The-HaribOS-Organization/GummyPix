#ifndef _GRADIENT_H
#define _GRADIENT_H


#include <stdint.h>
#include <math.h>
#include "../utils.h"
#include "convolution.h"
#include "image.h"

#define DIRECTION_X 0x1
#define DIRECTION_Y 0x0


static const int32_t sobel_x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
static const int32_t sobel_y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
static const int32_t scharr_x[3][3] = {{3, 0, -3}, {10, 0, -10}, {3, 0, -3}};
static const int32_t scharr_y[3][3] = {{3, 10, 3}, {0, 0, 0}, {-3, -10, -3}};


enum type_gradient {
    SOBEL_GRADIENT,
    SCHARR_GRADIENT
};

int32_t *gp_gradient(const gp_image_t *image, enum type_gradient type, uint8_t direction);

__attribute__((always_inline)) inline float gp_gradient_phase(gp_point_t point) {

    return (atan2f(point.y, point.x));
}

#endif
