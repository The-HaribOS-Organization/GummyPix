#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H


#include <stdint.h>
#include <math.h>
#include "image.h"



typedef struct {
    uint32_t min;
    uint32_t max;
} min_max_t;

typedef gp_pixels_t (*function)(gp_pixels_t);

static inline uint8_t int_pow_mod256(uint8_t base, uint32_t exp) {
    uint32_t result = 1;
    for (uint32_t i = 0; i < exp; i++) {
        result *= base;
    }
    return (uint8_t)(result % 256);
}


gp_pixels_t *gp_sqrt(const gp_image_t *image);
gp_pixels_t *gp_pow(const gp_image_t *image, uint32_t power);
gp_pixels_t *gp_log(const gp_image_t *image);
gp_pixels_t *gp_exp(const gp_image_t *image);
gp_pixels_t *gp_mul(const gp_image_t *image, uint32_t number);
gp_pixels_t *gp_apply_custom(const gp_image_t *image, function custom_fn);

min_max_t gp_min_max(const uint8_t *array, uint32_t size);

#endif
