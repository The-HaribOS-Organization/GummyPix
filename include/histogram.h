#ifndef _HISTOGRAM_H
#define _HISTOGRAM_H


#include <stdint.h>
#include "image.h"
#include "utils.h"



#define HISTOGRAM_LENGTH 256

uint32_t *gp_histogram(const gp_image_t *image, const uint8_t canal);
void gp_export_histogram(const char *filename, const uint32_t histogram[HISTOGRAM_LENGTH]);
float *gp_normalize_histogram(const uint32_t *histogram, gp_point_t dimension);
void equalize_histogram(const gp_image_t *image, uint32_t *histogram, uint8_t channel);

#endif
