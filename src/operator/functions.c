#include <stdint.h>
#include "image.h"
#include "operator/functions.h"



gp_pixels_t *gp_sqrt(const gp_image_t *image) {

    gp_pixels_t *output = (gp_pixels_t *)malloc(sizeof(gp_pixels_t) * image->dimension.x * image->dimension.y);

    for (uint32_t i = 0; i < image->dimension.y; i++) {
        for (uint32_t j = 0; j < image->dimension.x; j++)
            output[i * image->dimension.x + j] = (gp_pixels_t){
                (int32_t)sqrt(image->data[i * image->dimension.x + j].red) % 256,
                (int32_t)sqrt(image->data[i * image->dimension.x + j].green) % 256,
                (int32_t)sqrt(image->data[i * image->dimension.x + j].blue) % 256,
                0};
    }

    return output;
}

gp_pixels_t *gp_pow(const gp_image_t *image, uint32_t power) {

    gp_pixels_t *output = (gp_pixels_t *)malloc(sizeof(gp_pixels_t) * image->dimension.x * image->dimension.y);

    for (uint32_t i = 0; i < image->dimension.y; i++) {
        for (uint32_t j = 0; j < image->dimension.x; j++)
            output[i * image->dimension.x + j] = (gp_pixels_t){
                int_pow_mod256(image->data[i * image->dimension.x + j].red, power),
                int_pow_mod256(image->data[i * image->dimension.x + j].green, power),
                int_pow_mod256(image->data[i * image->dimension.x + j].blue, power),
                0};
    }

    return output;
}

gp_pixels_t *gp_log(const gp_image_t *image) {

    gp_pixels_t *output = (gp_pixels_t *)malloc(sizeof(gp_pixels_t) * image->dimension.x * image->dimension.y);

    for (uint32_t i = 0; i < image->dimension.y; i++) {
        for (uint32_t j = 0; j < image->dimension.x; j++)
            output[i * image->dimension.x + j] = (gp_pixels_t){
                ((uint32_t)log(image->data[i * image->dimension.x + j].red) % 256),
                ((uint32_t)log(image->data[i * image->dimension.x + j].green) % 256),
                ((uint32_t)log(image->data[i * image->dimension.x + j].blue) % 256),
                0};
    }

    return output;
}

gp_pixels_t *gp_log2(const gp_image_t *image) {

    gp_pixels_t *output = (gp_pixels_t *)malloc(sizeof(gp_pixels_t) * image->dimension.x * image->dimension.y);

    for (uint32_t i = 0; i < image->dimension.y; i++) {
        for (uint32_t j = 0; j < image->dimension.x; j++)
            output[i * image->dimension.x + j] = (gp_pixels_t){
                (int32_t)log2(image->data[i * image->dimension.x + j].red % 256),
                (int32_t)log2(image->data[i * image->dimension.x + j].green % 256),
                (int32_t)log2(image->data[i * image->dimension.x + j].blue % 256),
                0};
    }

    return output;
}

gp_pixels_t *gp_log10(const gp_image_t *image) {

    gp_pixels_t *output = (gp_pixels_t *)malloc(sizeof(gp_pixels_t) * image->dimension.x * image->dimension.y);

    for (uint32_t i = 0; i < image->dimension.y; i++) {
        for (uint32_t j = 0; j < image->dimension.x; j++)
            output[i * image->dimension.x + j] = (gp_pixels_t){
                (int32_t)log10(image->data[i * image->dimension.x + j].red % 256),
                (int32_t)log10(image->data[i * image->dimension.x + j].green % 256),
                (int32_t)log10(image->data[i * image->dimension.x + j].blue % 256),
                0};
    }

    return output;
}

gp_pixels_t *gp_exp(const gp_image_t *image) {

    gp_pixels_t *output = (gp_pixels_t *)malloc(sizeof(gp_pixels_t) * image->dimension.x * image->dimension.y);

    for (uint32_t i = 0; i < image->dimension.y; i++) {
        for (uint32_t j = 0; j < image->dimension.x; j++)
            output[i * image->dimension.x + j] = (gp_pixels_t){
                (int32_t)exp(image->data[i * image->dimension.x + j].red % 256),
                (int32_t)exp(image->data[i * image->dimension.x + j].green % 256),
                (int32_t)exp(image->data[i * image->dimension.x + j].blue % 256),
                0};
    }

    return output;
}

gp_pixels_t *gp_mul(const gp_image_t *image, uint32_t number) {

    gp_pixels_t *output = (gp_pixels_t *)malloc(sizeof(gp_pixels_t) * image->dimension.x * image->dimension.y);

    for (uint32_t i = 0; i < image->dimension.y; i++) {
        for (uint32_t j = 0; j < image->dimension.x; j++)
            output[i * image->dimension.x + j] = (gp_pixels_t){
                (int32_t)(image->data[i * image->dimension.x + j].red * number) % 256,
                (int32_t)(image->data[i * image->dimension.x + j].green * number) % 256,
                (int32_t)(image->data[i * image->dimension.x + j].blue * number) % 256,
                0};
    }

    return output;
}

gp_pixels_t *gp_apply_custom(const gp_image_t *image, function custom_fn) {

    gp_pixels_t *output = (gp_pixels_t *)malloc(sizeof(gp_pixels_t) * image->dimension.x * image->dimension.y);

    for (uint32_t i = 0; i < image->dimension.y; i++) {
        for (uint32_t j = 0; j < image->dimension.x; j++)
            output[i * image->dimension.x + j] = custom_fn(image->data[i * image->dimension.x + j]);
    }

    return output;
}
