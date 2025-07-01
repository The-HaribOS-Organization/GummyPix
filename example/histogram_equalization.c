#include <omp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <GummyPix/GummyPix.h>



int main(int argc, char **argv) {

    gp_image_t *image = gp_read_image("grayscale_lapin_adam.bmp");
    uint8_t *channel = gp_extract_channel(image, 0);
    min_max_t extremum = gp_min_max(channel, image->dimension.x * image->dimension.y);
    uint8_t diff = extremum.max - extremum.min;
    uint32_t cumul = 0;

    uint32_t *histogram = gp_histogram(image, 0);

    for (uint32_t i = 0; i < 256; i++) {

        cumul += histogram[i];
        histogram[i] = cumul;
    }

    for (uint32_t j = 0; j < image->dimension.x * image->dimension.y; j++) {

        uint32_t pos = (image->data[j].red - extremum.min) * 255 / diff;
        
        if (pos >= 0 && pos < 256) {
            uint8_t value = extremum.min + diff * histogram[pos] / (image->dimension.x * image->dimension.y);
            image->data[j] = (gp_pixels_t){value, value, value, 0};
        }
    }

    gp_write_image("equalized_grayscale_lapin_adam.bmp", image);
    gp_close_image(image);

    return EXIT_SUCCESS;
}
