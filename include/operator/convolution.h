#ifndef _CONVOLUTION_H
#define _CONVOLUTION_H


#include <stdint.h>
#include "../utils.h"


_Float32 *gp_convolution(uint8_t *array, gp_point_t dimension, gp_point_t kernel_size, const _Float32 *noyau);

#endif
