#ifndef _BOOLEAN_H
#define _BOOLEAN_H


#include <stdint.h>
#include "image.h"



#define NOT(pixels, canal) {( \
    return ((canal == 0) ? ~pixel.red : (canal == 1) ? ~pixel.green : ~pixel.blue) \
)}


uint8_t *gp_and(gp_image_t *A, gp_image_t *B, uint8_t canal);
uint8_t *gp_or(gp_image_t *A, gp_image_t *B, uint8_t canal);
uint8_t *gp_xor(gp_image_t *A, gp_image_t *B, uint8_t canal);
uint8_t *gp_not(gp_image_t *image, uint8_t canal);

#endif
