#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "image.h"
#include "format/bitmap.h"


image_t *read_image(char *file_path) {

    struct stat st;
    uint8_t *array;
    bitmap_t *bitmap;
    image_t *picture = (image_t *)malloc(sizeof(image_t));

    FILE *image = fopen(file_path, "rb");
    if (image == NULL) return NULL;

    stat(file_path, &st);
    array = (uint8_t *)malloc(sizeof(uint8_t) * (int)st.st_size);

    fread(array, st.st_size, 1, image);
    bitmap = parse_bitmap(array);

    if ((bitmap->bpp != 24 && bitmap->bpp != 32) || !is_bitmap(bitmap)) {

        fprintf(stderr, "Erreur, le format de l'image n'est pas respecté.\n");
        return NULL;
    }

    picture->data = (pixels_t *)malloc(sizeof(pixels_t) * bitmap->bitmap_width * bitmap->bitmap_height);

    for (uint32_t i = 0; i < bitmap->bitmap_width * bitmap->bitmap_height; i++)
        picture->data[i] = (pixels_t){
            array[bitmap->offset_pixel_array + i * 3 + 2],
            array[bitmap->offset_pixel_array + i * 3 + 1],
            array[bitmap->offset_pixel_array + i * 3],
            (bitmap->bpp == 32) ? array[bitmap->offset_pixel_array + i * 3 + 3] : 0
        };

    picture->width = bitmap->bitmap_width;
    picture->height = bitmap->bitmap_height;
    picture->bpp = bitmap->bpp;
    picture->size = bitmap->image_size;

    free(array);
    fclose(image);

    return picture;
}

void write_image(char *file_path, image_t *image_write) {

    FILE *image_w = fopen(file_path, "wb");

    bitmap_t bitmap_header = {
        BITMAP_SIGNATURE,
        image_write->size + sizeof(bitmap_t),
        0,
        0,
        sizeof(bitmap_t),
        sizeof(bitmap_t) - 14,
        image_write->width,
        image_write->height,
        1,
        image_write->bpp,
        0,
        image_write->width * image_write->height,
        (uint32_t)(DEFAULT_DPI * INCHES_PER_METER),
        (uint32_t)(DEFAULT_DPI * INCHES_PER_METER),
        0,
        0
    };

    fwrite(&bitmap_header, sizeof(bitmap_t), 1, image_w);
    for (uint32_t i = 0; i < image_write->width * image_write->height; i++) {

        fwrite(&image_write->data[i].blue, sizeof(uint8_t), 1, image_w);
        fwrite(&image_write->data[i].green, sizeof(uint8_t), 1, image_w);
        fwrite(&image_write->data[i].red, sizeof(uint8_t), 1, image_w);
        
        if (image_write->bpp == 32) fwrite(&image_write->data[i].alpha, sizeof(uint8_t), 1, image_w);
    }

    fclose(image_w);
    return;
}