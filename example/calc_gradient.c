#include <GummyPix/GummyPix.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



int main(int argc, char **argv) {

    if (argc == 1) {
        fprintf(stderr, "Erreur, vous devez saisir le nom du fichier.\n");
        return EXIT_FAILURE;
    }

    gp_image_t *image = gp_read_image(argv[1]);
    int32_t *grad_x = gp_gradient(image, SOBEL_GRADIENT, DIRECTION_X);
    int32_t *grad_y = gp_gradient(image, SOBEL_GRADIENT, DIRECTION_Y);

    for (uint32_t i = 0; i < image->dimension.y; i++) {
        for (uint32_t j = 0; j < image->dimension.x; j++) {

            double norme = gp_norm((gp_point_t){grad_x[i * image->dimension.x + j], grad_y[i * image->dimension.x + j]});
            image->data[i * image->dimension.x + j] = (gp_pixels_t){(uint8_t)norme, (uint8_t)norme, (uint8_t)norme, 0};
        }
    }

    gp_write_image("gradient.bmp", image);
    gp_close_image(image);

    return EXIT_SUCCESS;
}