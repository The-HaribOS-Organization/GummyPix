#ifndef _CONVOLUTION_H
#define _CONVOLUTION_H


#include <stdint.h>
#include "../utils.h"


int32_t *gp_convolution(int32_t *array, gp_point_t dimension, gp_point_t kernel_size, const int32_t noyau[kernel_size.x][kernel_size.y]);

#endif
