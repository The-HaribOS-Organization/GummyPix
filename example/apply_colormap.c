#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <GummyPix/GummyPix.h>

int main(int argc, char **argv) {
    
    gp_image_t *image = gp_read_image("lapin_adam.bmp"), *write_image = gp_create_image(image->dimension);
    uint8_t *grayscale = gp_rgb_to_grayscale(image);

    gp_float_pixels_t *color_map = gp_read_color_map("turbo_r.gummycm");
    gp_pixels_t *pixels = gp_apply_color_map(grayscale, color_map, image->dimension);

    memcpy(write_image->data, pixels, sizeof(gp_pixels_t) * image->dimension.x * image->dimension.y);

    gp_write_image("color_map_lapin_adam.bmp", write_image);
    gp_close_image(image);
    gp_close_image(write_image);
    free(color_map);
    free(grayscale);
    free(pixels);
    return EXIT_SUCCESS;
}
