#ifndef _COLOR_H
#define _COLOR_H


#include <stdint.h>
#include "image.h"


#define COLOR_MAP_ENTRY_NUM 256
#define COLOR_MAP_BYTE_SIZE 3072


__attribute__((always_inline)) inline gp_pixels_t gp_rgb_2_bgr(gp_pixels_t pixel) {

    pixel.red = pixel.red ^ pixel.blue;
    pixel.blue = pixel.blue ^ pixel.red;
    pixel.red = pixel.red ^ pixel.blue;
    return pixel;
}

__attribute__((always_inline)) inline gp_pixels_t gp_alpha_blend(gp_pixels_t current_color, gp_pixels_t color_read, uint8_t alpha) {

    return (gp_pixels_t){((color_read.red * alpha + current_color.red * (255 - alpha)) / 255),
    ((color_read.green * alpha + current_color.green * (255 - alpha)) / 255),
    ((color_read.blue * alpha + current_color.blue * (255 - alpha)) / 255), 0};
}


uint8_t *gp_extract_channel(const gp_image_t *image, uint8_t canal);
uint8_t *gp_rgb_to_grayscale(const gp_image_t *image);
void gp_linear_interpolate(gp_image_t *image, gp_point_t dimension, gp_point_t lenght, gp_pixels_t start_color, gp_pixels_t end_color);
gp_float_pixels_t *gp_read_color_map(const char *color_map);
gp_pixels_t *gp_apply_color_map(const uint8_t *grayscale_picture, const gp_float_pixels_t *color_map, const gp_point_t size);

#endif
