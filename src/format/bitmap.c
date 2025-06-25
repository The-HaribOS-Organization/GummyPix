#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "format/bitmap.h"


bitmap_t *parse_bitmap(uint8_t *image) {
    
    bitmap_t *header = (bitmap_t *)malloc(sizeof(bitmap_t));
    memcpy(header, image, sizeof(bitmap_t));

    return header;
}