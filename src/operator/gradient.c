#include <stdint.h>
#include <stdlib.h>
#include "image.h"
#include "operator/gradient.h"
#include "operator/convolution.h"


int32_t *gradient(const image_t *image, enum type_gradient type, uint8_t direction) {

    if (image->data == NULL || direction > 0x1) return NULL;

    if (type == SOBEL_GRADIENT)
        return convolution(
            array,
            image->dimension,
            (point_t){3, 3}, (direction == 1) ? sobel_x : sobel_y);
    else if (type == SCHARR_GRADIENT)
        return convolution(
            array,
            image->dimension,
            (point_t){3, 3}, (direction == 1) ? scharr_x : scharr_y);
}