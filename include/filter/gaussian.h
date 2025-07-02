#ifndef _GAUSSIAN_H
#define _GAUSSIAN_H

#include <stdint.h>


#define FILTER_SIZE(sigma) (6 * sigma + 1)


__attribute__((always_inline)) inline uint32_t gp_get_size_filter(float sigma) {

    return ((uint32_t)FILTER_SIZE(sigma) % 2 == 0) ? FILTER_SIZE(sigma) + 1 : FILTER_SIZE(sigma);
}

_Float32 *gp_gaussian_filter(_Float32 sigma);

#endif
