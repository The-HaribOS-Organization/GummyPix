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
} gp_pixels_t;

typedef struct {
    gp_point_t dimension;
    uint32_t size;
    uint32_t bpp;
    gp_pixels_t *data;
} gp_image_t;


__attribute__((always_inline)) inline void gp_close_image(gp_image_t *picture) {

    free(picture->data);
    free(picture);
}

gp_image_t *gp_read_image(char *file_path);
gp_image_t *gp_create_image(gp_point_t size);
void gp_write_image(char *file_path, gp_image_t *image_write);

#endif
