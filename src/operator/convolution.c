#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <omp.h>
#include "operator/convolution.h"
#include "utils.h"


_Float32 *gp_convolution(uint8_t *array, gp_point_t dimension, gp_point_t kernel_size, const _Float32 *noyau) {

    if (kernel_size.x % 2 == 0 || kernel_size.y % 2 == 0) {
        fprintf(stderr, "Erreur, la taille du filtre doit etre impair.\n");
        return NULL;
    }

    _Float32 *output = (_Float32 *)malloc(sizeof(_Float32) * dimension.x * dimension.y);
    gp_point_t padding = {
        kernel_size.x / 2,
        kernel_size.y / 2};


    #pragma omp parallel for collapse(2)
    for (uint32_t y = 0; y < dimension.y; ++y) {
        for (uint32_t x = 0; x < dimension.x; ++x) {

            _Float32 sum = 0;
            for (uint32_t i = 0; i < kernel_size.y; i++) {
                for (uint32_t j = 0; j < kernel_size.x; j++) {

                    if ((y + i - padding.y) >= 0 && (y + i - padding.y) < dimension.y && (x + j - padding.x) >= 0 && (x + j - padding.x) < dimension.x)
                        sum += array[(y + i - padding.y) * dimension.x + (x + j - padding.x)] * noyau[i * kernel_size.x + j];
                }
            }

            output[y * dimension.x + x] = sum;
        }
    }

    return output;
}
