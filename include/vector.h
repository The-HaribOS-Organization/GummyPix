#ifndef _VECTOR_H
#define _VECTOR_H

#include <stdint.h>
#include <math.h>
#include "utils.h"


__attribute__((always_inline)) inline double norm(point_t coord) {

    return sqrt(coord.x * coord.x + coord.y * coord.y);
}

#endif
