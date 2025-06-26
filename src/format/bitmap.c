#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "format/bitmap.h"


gp_bitmap_t *gp_parse_bitmap(uint8_t *image) {
    
    gp_bitmap_t *header = (gp_bitmap_t *)malloc(sizeof(gp_bitmap_t));
    memcpy(header, image, sizeof(gp_bitmap_t));

    return header;
}