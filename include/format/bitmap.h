#ifndef _BITMAP_H

#include <stdint.h>
#include <stdbool.h>


#define BITMAP_SIGNATURE 0x4D42
#define DEFAULT_DPI 96
#define INCHES_PER_METER 39.3701

#define BPP32_BITMAP_IMG 32
#define BPP24_BITMAP_IMG 24


typedef struct {

    uint16_t header_field;
    uint32_t size;
    uint16_t reserved[2];
    uint32_t offset_pixel_array;
    uint32_t header_size;
    uint32_t bitmap_width;
    uint32_t bitmap_height;
    uint16_t color_plane;
    uint16_t bpp;
    uint32_t compression_method;
    uint32_t image_size;
    uint32_t horizontal_resolution;
    uint32_t vertical_resolution;
    uint32_t color_number;
    uint32_t important_color_number;
} __attribute__((packed)) bitmap_t;


bitmap_t *parse_bitmap(uint8_t *image);

__attribute__((always_inline)) inline bool is_bitmap(bitmap_t *image) {
    return (image->header_field == BITMAP_SIGNATURE) ? true : false;
}


#endif
