#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <omp.h>
#include <immintrin.h>
#include "image.h"
#include "histogram.h"
#include "color.h"
#include "operator/functions.h"



uint32_t *gp_histogram(const gp_image_t *image, const uint8_t canal) {

    if (image == NULL || image->data == NULL || canal > 2) {
        fprintf(stderr, "Erreur, gp_image_t est nul.\n");
        return NULL;
    }

    uint32_t max_i = image->dimension.x * image->dimension.y - ((image->dimension.x * image->dimension.y) % 32);
    uint8_t *channel = gp_extract_channel(image, canal);
    uint32_t *histogram = (uint32_t *)malloc(HISTOGRAM_LENGTH * sizeof(uint32_t));
    
    
    memset(histogram, 0, HISTOGRAM_LENGTH * sizeof(uint32_t));

    #pragma omp parallel for
    for (uint32_t i = 0; i < max_i; i += 32) {

        __m256i block = _mm256_loadu_si256((__m256i *)&channel[i]);
        __attribute__((aligned(32))) uint8_t values[32];
        _mm256_store_si256((__m256i *)values, block);

        for (uint32_t vi = 0; vi < 32; vi++) {

            uint8_t val_i = values[vi];
            bool first = true;

            for (uint32_t vj = 0; vj < vi; vj++) {
                if (values[vj] == val_i) {
                    first = false;
                    break;
                }
            }

            if (first) {

                uint32_t count = 0;
                for (uint32_t vk = 0; vk < 32; vk++) {
                    if (values[vk] == val_i) count++;
                }

                #pragma omp atomic
                histogram[val_i] += count;
            }
        }
    }

    for (uint32_t i = ((image->dimension.x * image->dimension.y) / 32) * 32; i < image->dimension.x * image->dimension.y; i++) histogram[channel[i]]++;

    return histogram;
}


void gp_export_histogram(const char *filename, const uint32_t histogram[HISTOGRAM_LENGTH]) {

    FILE *fichier = fopen(filename, "a");
    if (fichier == NULL || histogram == NULL) {
        fprintf(stderr, "Erreur, impossible d'écrire l'histogramme dans le répertoire.\n");
        return;
    }

    fprintf(fichier, "pixel_value,frequency\n");
    for (uint16_t i = 0; i < HISTOGRAM_LENGTH; i++) {
        fprintf(fichier, "%d,%d\n", i, histogram[i]);
    }

    fclose(fichier);
    return;
}


float *gp_normalize_histogram(const uint32_t *histogram, gp_point_t dimension) {

    static float normalized[256] = {0};

    for (uint16_t i = 0; i < 256; i++) normalized[i] = (float)histogram[i] / (dimension.x * dimension.y);
    return normalized;
}

void equalize_histogram(const gp_image_t *image, uint32_t *histogram, uint8_t channel) {

    if (histogram == NULL || image == NULL || image->data == NULL || channel > 2) {
        fprintf(stderr, "Canal saisit incorrect.\n");
        return;
    }

    uint8_t cdf[256] = {0};
    uint8_t *canal = gp_extract_channel(image, channel);
    min_max_t extremum = gp_min_max(canal, image->dimension.x * image->dimension.y);
    uint8_t diff = extremum.max - extremum.min;
    uint32_t cumul = 0;
    
    for (uint32_t i = 0; i < 256; i++) {

        cumul += histogram[i];
        histogram[i] = cumul;
    }

    #pragma omp parallel for
    for (uint32_t j = 0; j < image->dimension.x * image->dimension.y; j++) {

        uint8_t value = (channel == 0) ? image->data[j].red :
                        (channel == 1) ? image->data[j].green :
                        image->data[j].blue;

        uint32_t pos = (value - extremum.min) * 255 / diff;
        
        if (pos >= 0 && pos < 256) {

            if (channel == 0) image->data[j].red = extremum.min + diff * histogram[pos] / (image->dimension.x * image->dimension.y);
            else if (channel == 1) image->data[j].green = extremum.min + diff * histogram[pos] / (image->dimension.x * image->dimension.y);
            else image->data[j].blue = extremum.min + diff * histogram[pos] / (image->dimension.x * image->dimension.y);
        }
    }

    free(canal);
}
