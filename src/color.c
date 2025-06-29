#include <stdint.h>
#include <omp.h>
#include "color.h"
#include "utils.h"
#include "shape.h"
#include "image.h"



void gp_linear_interpolate(gp_image_t *image, gp_point_t dimension, gp_point_t lenght, gp_pixels_t start_color, gp_pixels_t end_color) {

	for (float i = dimension.y; i < dimension.y + lenght.y + 1; i++) {

		gp_draw_line(image, (gp_line_t){
                (gp_point_t){dimension.x, i},
                (gp_point_t){(dimension.x + lenght.x), i},
                (gp_pixels_t){(1 - (i / (dimension.y + lenght.y))) * (float)start_color.red + (float)end_color.red * i / (dimension.y + lenght.y),
                (1 - (i / (dimension.y + lenght.y))) * (float)start_color.green + (float)end_color.green * i / (dimension.y + lenght.y),
                (1 - (i / (dimension.y + lenght.y))) * (float)start_color.blue + (float)end_color.blue * i / (dimension.y + lenght.y), 0}});
	}

    return;
}

uint8_t *gp_extract_channel(const gp_image_t *image, uint8_t canal) {

    if (image == NULL || image->data == NULL || canal > 2) return NULL;

    uint8_t *channel = (uint8_t *)malloc(sizeof(uint8_t) * image->dimension.x * image->dimension.y);

    #pragma omp parallel for
    for (uint32_t i = 0; i < image->dimension.y * image->dimension.x; i++)
        channel[i] = (canal == 0) ? image->data[i].red : (canal == 1) ? image->data[i].green : image->data[i].blue;

    return channel;
}
