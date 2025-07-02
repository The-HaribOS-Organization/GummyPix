#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
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

uint8_t *gp_rgb_to_grayscale(const gp_image_t *image) {

    uint8_t *grayscale_image = (uint8_t *)malloc(sizeof(uint8_t) * image->dimension.x * image->dimension.y);

    #pragma omp parallel for
    for (uint32_t i = 0; i < image->dimension.x * image->dimension.y; i++)
        grayscale_image[i] = 0.298 * image->data[i].red + 0.587 * image->data[i].green + 0.114 * image->data[i].blue;

    return grayscale_image;
}

gp_float_pixels_t *gp_read_color_map(const char *color_map) {

    struct stat st;
    FILE *color_map_flow = fopen(color_map, "rb");
    gp_float_pixels_t *color_map_array = (gp_float_pixels_t *)malloc(sizeof(gp_float_pixels_t) * COLOR_MAP_ENTRY_NUM);

    stat(color_map, &st);
    if (st.st_size != COLOR_MAP_BYTE_SIZE) {

        fprintf(stderr, "Erreur, color map non valide.\n");
        return NULL;
    }

    size_t block_read = fread(color_map_array, sizeof(gp_float_pixels_t), COLOR_MAP_ENTRY_NUM, color_map_flow);
    fclose(color_map_flow);
    
    return (block_read != COLOR_MAP_ENTRY_NUM) ? NULL : color_map_array;
}

gp_pixels_t *gp_apply_color_map(const uint8_t *grayscale_picture, const gp_float_pixels_t *color_map, const gp_point_t size) {


    gp_pixels_t *pixels = (gp_pixels_t *)malloc(sizeof(gp_pixels_t) * size.x * size.y);
    for (uint32_t i = 0; i < size.x * size.y; i++)
        pixels[i] = (gp_pixels_t){
            color_map[grayscale_picture[i]].red * grayscale_picture[i],
            color_map[grayscale_picture[i]].green * grayscale_picture[i],
            color_map[grayscale_picture[i]].blue * grayscale_picture[i], 0};

    return pixels;
}
