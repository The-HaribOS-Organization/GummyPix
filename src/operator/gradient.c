#include <stdint.h>
#include <stdlib.h>
#include "operator/gradient.h"
#include "operator/convolution.h"
#include "vector.h"
#include "image.h"



int32_t *gp_gradient(const gp_image_t *image, enum type_gradient type, uint8_t direction) {

    if (image->data == NULL || direction > 0x1) return NULL;

    int32_t *result = NULL, *array = (int32_t *)malloc(sizeof(int32_t) * image->dimension.x * image->dimension.y);
    for (uint32_t i = 0; i < image->dimension.y; i++) {
        for (uint32_t j = 0; j < image->dimension.x; j++)
            array[i * image->dimension.x + j] = (int32_t)((float)(0.298 * image->data[i * image->dimension.x + j].red + 0.587 * image->data[i * image->dimension.x + j].green + 0.114 * image->data[i * image->dimension.x + j].blue));
    }

    if (type == SOBEL_GRADIENT) result = gp_convolution(array, image->dimension, (gp_point_t){3, 3}, (direction == 1) ? sobel_x : sobel_y);
    else if (type == SCHARR_GRADIENT) result = gp_convolution(array, image->dimension, (gp_point_t){3, 3}, (direction == 1) ? scharr_x : scharr_y);

    free(array);
    return result;
}
