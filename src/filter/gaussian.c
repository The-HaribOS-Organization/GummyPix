#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "filter/gaussian.h"


_Float32 *gp_gaussian_filter(_Float32 sigma) {

    if (sigma <= 0.0) {
        fprintf(stderr, "Erreur, sigma doit être superieur a 0.0.\n");
        return NULL;
    }

    uint16_t size = gp_get_size_filter(sigma);
    _Float32 *filter = malloc(sizeof(_Float32) * size * size), sum = 0;
    if (!filter) {
        fprintf(stderr, "Erreur avec malloc.\n");
        return NULL;
    }

    for (uint16_t i = 0; i < size; i++) {
        for (uint16_t j = 0; j < size; j++) {
            filter[i * size + j] = (1 / (2 * M_PI * sigma * sigma)) * expf(-((i - size / 2) * (i - size / 2) + (j - size / 2) * (j - size / 2)) / (2 * sigma * sigma));
            sum += filter[i * size + j];
        }
    }

    for (uint16_t i = 0; i < size * size; i++) filter[i] /= sum;

    return filter;
}
