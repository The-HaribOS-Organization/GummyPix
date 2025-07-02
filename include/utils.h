#ifndef _UTILS_H
#define _UTILS_H


#include <stdint.h>


typedef struct {

    uint32_t x;
    uint32_t y;
} gp_point_t;


typedef enum {
    GP_UINT8_T_ARRAY,
    GP_FLOAT32_T_ARRAY
} gp_array_type;

#endif
