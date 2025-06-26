#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H


#include <stdint.h>
#include <math.h>
#include "image.h"


typedef gp_pixels_t (*function)(gp_pixels_t);

gp_pixels_t *gp_sqrt(const gp_image_t *image);
gp_pixels_t *gp_pow(const gp_image_t *image, uint32_t power);
gp_pixels_t *gp_log(const gp_image_t *image);
gp_pixels_t *gp_log2(const gp_image_t *image);
gp_pixels_t *gp_log10(const gp_image_t *image);
gp_pixels_t *gp_exp(const gp_image_t *image);
gp_pixels_t *gp_mul(const gp_image_t *image, uint32_t number);
gp_pixels_t *gp_apply_custom(const gp_image_t *image, function custom_fn);

#endif
