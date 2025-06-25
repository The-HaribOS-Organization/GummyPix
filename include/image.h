#ifndef _IMAGE_H
#define _IMAGE_H


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "utils.h"



typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
} pixels_t;

typedef struct {
    point_t dimension;
    uint32_t size;
    uint32_t bpp;
    pixels_t *data;
} image_t;


__attribute__((always_inline)) inline void close_image(image_t *picture) {

    free(picture->data);
    free(picture);
}

image_t *read_image(char *file_path);
void write_image(char *file_path, image_t *image_write);

#endif
