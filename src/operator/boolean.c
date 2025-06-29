#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>
#include "image.h"
#include "utils.h"
#include "color.h"
#include "operator/boolean.h"



uint8_t *gp_and(gp_image_t *A, gp_image_t *B, uint8_t canal) {

    if (A->dimension.x != B->dimension.x || A->dimension.y != B->dimension.y) {
        fprintf(stderr, "Erreur les images doivent faire la meme taille.\n");
        return NULL;
    } else if (A == NULL || A->data == NULL) {
        return NULL;
    }

    uint8_t *image = (uint8_t *)malloc(sizeof(uint8_t) * A->dimension.x * A->dimension.y);
    uint8_t *A_channel = gp_extract_channel(A, canal), *B_channel = gp_extract_channel(B, canal);

    uint32_t i = 0;
    for (; i + 32 < A->dimension.x * A->dimension.y; i += 32) {

        __m256i va = _mm256_loadu_si256((const __m256i *)&A_channel[i]);
        __m256i vb = _mm256_loadu_si256((const __m256i *)&B_channel[i]);
        __m256i vxor = _mm256_and_si256(va, vb);

        _mm256_storeu_si256((__m256i *)&image[i], vxor);
    }

    for (; i < A->dimension.x * A->dimension.y; i++)
        image[i] = A_channel[i] ^ B_channel[i];

    return image;
}

uint8_t *gp_or(gp_image_t *A, gp_image_t *B, uint8_t canal) {

    if (A->dimension.x != B->dimension.x || A->dimension.y != B->dimension.y) {
        fprintf(stderr, "Erreur les images doivent faire la meme taille.\n");
        return NULL;
    } else if (A == NULL || A->data == NULL) {
        return NULL;
    }

    uint8_t *image = (uint8_t *)malloc(sizeof(uint8_t) * A->dimension.x * A->dimension.y);
    uint8_t *A_channel = gp_extract_channel(A, canal), *B_channel = gp_extract_channel(B, canal);

    uint32_t i = 0;
    for (; i + 32 < A->dimension.x * A->dimension.y; i += 32) {

        __m256i va = _mm256_loadu_si256((const __m256i *)&A_channel[i]);
        __m256i vb = _mm256_loadu_si256((const __m256i *)&B_channel[i]);
        __m256i vxor = _mm256_or_si256(va, vb);

        _mm256_storeu_si256((__m256i *)&image[i], vxor);
    }

    for (; i < A->dimension.x * A->dimension.y; i++)
        image[i] = A_channel[i] ^ B_channel[i];

    return image;
}

uint8_t *gp_xor(gp_image_t *A, gp_image_t *B, uint8_t canal) {

    if (A->dimension.x != B->dimension.x || A->dimension.y != B->dimension.y) {
        fprintf(stderr, "Erreur les images doivent faire la meme taille.\n");
        return NULL;
    } else if (A == NULL || A->data == NULL) {
        return NULL;
    }

    uint8_t *image = (uint8_t *)malloc(sizeof(uint8_t) * A->dimension.x * A->dimension.y);
    uint8_t *A_channel = gp_extract_channel(A, canal), *B_channel = gp_extract_channel(B, canal);

    uint32_t i = 0;
    for (; i + 32 < A->dimension.x * A->dimension.y; i += 32) {

        __m256i va = _mm256_loadu_si256((const __m256i *)&A_channel[i]);
        __m256i vb = _mm256_loadu_si256((const __m256i *)&B_channel[i]);
        __m256i vxor = _mm256_xor_si256(va, vb);

        _mm256_storeu_si256((__m256i *)&image[i], vxor);
    }

    for (; i < A->dimension.x * A->dimension.y; i++)
        image[i] = A_channel[i] ^ B_channel[i];

    return image;
}

uint8_t *gp_not(gp_image_t *image, uint8_t canal) {

    if (image == NULL || image->data == NULL) return NULL;
    uint8_t *array = (uint8_t *)malloc(sizeof(uint8_t) * image->dimension.x * image->dimension.y);
    
    for (uint32_t i = 0; i < image->dimension.y; i++) {
        for (uint32_t j = 0; j < image->dimension.x; j++)
        array[i * image->dimension.x + j] = (canal == 0) ?
            ~image->data[i * image->dimension.x + j].red :
            (canal == 1) ? ~image->data[i * image->dimension.x + j].green :
            ~image->data[i * image->dimension.x + j].blue;
    }

    return array;
}
