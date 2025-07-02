#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <sys/stat.h>
#include "format/bitmap.h"
#include "image.h"



gp_image_t *gp_read_image(char *file_path) {

    struct stat st;
    uint8_t *array;
    gp_bitmap_t *bitmap;
    gp_image_t *picture = (gp_image_t *)malloc(sizeof(gp_image_t));

    FILE *image = fopen(file_path, "rb");
    if (image == NULL) return NULL;

    stat(file_path, &st);
    array = (uint8_t *)malloc(sizeof(uint8_t) * (int)st.st_size);

    if (fread(array, st.st_size, 1, image) != 1) {
        fprintf(stderr, "Erreur de lecture de l'image.\n");
        return NULL;
    }

    bitmap = gp_parse_bitmap(array);
    if ((bitmap->bpp != 24 && bitmap->bpp != 32) || !gp_is_bitmap(bitmap)) {

        fprintf(stderr, "Erreur, le format de l'image n'est pas respecté.\n");
        return NULL;
    }

    picture->data = (gp_pixels_t *)malloc(sizeof(gp_pixels_t) * bitmap->bitmap_width * bitmap->bitmap_height);

    for (uint32_t i = 0; i < bitmap->bitmap_width * bitmap->bitmap_height; i++)
        picture->data[i] = (gp_pixels_t){
            array[bitmap->offset_pixel_array + i * 3 + 2],
            array[bitmap->offset_pixel_array + i * 3 + 1],
            array[bitmap->offset_pixel_array + i * 3],
            (bitmap->bpp == 32) ? array[bitmap->offset_pixel_array + i * 3 + 3] : 0
        };

    picture->dimension.x = bitmap->bitmap_width;
    picture->dimension.y = bitmap->bitmap_height;
    picture->bpp = bitmap->bpp;
    picture->size = bitmap->image_size;

    free(array);
    fclose(image);

    return picture;
}

void gp_write_image(char *file_path, gp_image_t *image_write) {

    FILE *image_w = fopen(file_path, "wb");

    gp_bitmap_t bitmap_header = {
        BITMAP_SIGNATURE,
        image_write->size + sizeof(gp_bitmap_t),
        0,
        0,
        sizeof(gp_bitmap_t),
        sizeof(gp_bitmap_t) - 14,
        image_write->dimension.x,
        image_write->dimension.y,
        1,
        image_write->bpp,
        0,
        image_write->dimension.x * image_write->dimension.y,
        (uint32_t)(DEFAULT_DPI * INCHES_PER_METER),
        (uint32_t)(DEFAULT_DPI * INCHES_PER_METER),
        0,
        0
    };

    fwrite(&bitmap_header, sizeof(gp_bitmap_t), 1, image_w);
    for (uint32_t i = 0; i < image_write->dimension.x * image_write->dimension.y; i++) {

        fwrite(&image_write->data[i].blue, sizeof(uint8_t), 1, image_w);
        fwrite(&image_write->data[i].green, sizeof(uint8_t), 1, image_w);
        fwrite(&image_write->data[i].red, sizeof(uint8_t), 1, image_w);
        
        if (image_write->bpp == 32) fwrite(&image_write->data[i].alpha, sizeof(uint8_t), 1, image_w);
    }

    fclose(image_w);
    return;
}

gp_image_t *gp_create_image(gp_point_t size) {

    gp_image_t *new_image = (gp_image_t *)malloc(sizeof(gp_image_t));

    new_image->dimension = size;
    new_image->bpp = 24;
    new_image->size = size.x * size.y;
    new_image->data = (gp_pixels_t *)malloc(sizeof(gp_pixels_t) * size.x * size.y);

    return new_image;
}
