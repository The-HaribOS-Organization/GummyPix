#include <stdint.h>
#include <stdlib.h>
#include "operator/gradient.h"
#include "operator/convolution.h"
#include "vector.h"
#include "image.h"



_Float32 *gp_gradient(const gp_image_t *image, enum type_gradient type, uint8_t direction) {

    if (image->data == NULL || direction > 0x1) return NULL;

    _Float32 *result = NULL;
    uint8_t *array = (uint8_t *)malloc(sizeof(uint8_t) * image->dimension.x * image->dimension.y);
    for (uint32_t i = 0; i < image->dimension.y; i++) {
        for (uint32_t j = 0; j < image->dimension.x; j++)
            array[i * image->dimension.x + j] = (uint8_t)((_Float32)(0.298 * image->data[i * image->dimension.x + j].red + 0.587 * image->data[i * image->dimension.x + j].green + 0.114 * image->data[i * image->dimension.x + j].blue));
    }

    if (type == SOBEL_GRADIENT) result = gp_convolution(array, image->dimension, (gp_point_t){3, 3}, (direction == 1) ? sobel_x : sobel_y);
    else if (type == SCHARR_GRADIENT) result = gp_convolution(array, image->dimension, (gp_point_t){3, 3}, (direction == 1) ? scharr_x : scharr_y);

    free(array);
    return result;
}
