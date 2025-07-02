#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <GummyPix/GummyPix.h>



int main(int argc, char **argv) {

    gp_image_t *image = gp_read_image("lapin_adam.bmp"), *write_image = gp_create_image(image->dimension);
    uint8_t *grayscale = gp_rgb_to_grayscale(image);

    _Float32 *gaussian = gp_gaussian_filter(2);
    uint16_t size = gp_get_size_filter(2);
    
    _Float32 *result = gp_convolution(grayscale, write_image->dimension, (gp_point_t){size, size}, gaussian);
    for (uint32_t i = 0; i < write_image->dimension.x * write_image->dimension.y; i++)
        write_image->data[i] = (gp_pixels_t){(double)result[i], (double)result[i], (double)result[i], 0};

    gp_write_image("gaussian_filter_lapin_adam.bmp", write_image);
    gp_close_image(image);
    gp_close_image(write_image);
    free(grayscale);
    free(gaussian);
    free(result);
    return EXIT_SUCCESS;
}
