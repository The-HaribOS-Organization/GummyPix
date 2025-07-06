#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <complex.h>
#include <omp.h>
#include <math.h>
#include "fft.h"



complex _Float64 *gp_fft(complex _Float64 *array, uint32_t N) {

    if (N == 1) return array;
    
    complex _Float64 *even = (complex _Float64 *)malloc(sizeof(complex _Float64) * N / 2);
    complex _Float64 *odd = (complex _Float64 *)malloc(sizeof(complex _Float64) * N / 2);
    
    #pragma omp paralle for
    for (uint32_t i = 0; i < N / 2; i++) {
        even[i] = (complex _Float64)array[2 * i];
        odd[i] = (complex _Float64)array[2 * i + 1];
    }

    complex _Float64 *fft_even = gp_fft(even, N / 2), *fft_odd = gp_fft(odd, N / 2);
    complex _Float64 *result = (complex _Float64 *)malloc(N * sizeof(complex _Float64));

    #pragma omp paralle for
    for (uint32_t k = 0; k < N / 2; k++) {
        result[k] = fft_even[k] + cexp(-2.0 * M_PI * I * k / (double)N) * fft_odd[k];
        result[k + (uint32_t)N / 2] = fft_even[k] - (complex _Float64)cexp(-2.0 * M_PI * I * k / N) * fft_odd[k];
    }

    free(even);
    free(odd);
    return result;
}


complex _Float64 *gp_ifft(complex _Float64 *array, uint32_t N) {

    if (N == 1) return array;

    complex _Float64 *even = (complex _Float64 *)malloc(sizeof(complex _Float64) * N / 2);
    complex _Float64 *odd = (complex _Float64 *)malloc(sizeof(complex _Float64) * N / 2);

    #pragma omp parallel for
    for (uint32_t i = 0; i < N / 2; i++) {
        even[i] = (complex _Float64)array[2 * i];
        odd[i] = (complex _Float64)array[2 * i + 1];
    }

    complex _Float64 *ifft_even = gp_ifft(even, N / 2), *ifft_odd = gp_ifft(odd, N / 2);
    complex _Float64 *result = (complex _Float64 *)malloc(N * sizeof(complex _Float64));

    #pragma omp parallel for
    for (uint32_t k = 0; k < N / 2; k++) {
        result[k] = ifft_even[k] + cexp(2.0 * M_PI * I * k / (double)N) * ifft_odd[k];
        result[k + (uint32_t)N / 2] = ifft_even[k] - (complex _Float64)cexp(2.0 * M_PI * I * k / N) * ifft_odd[k];
    }

    for (uint32_t i = 0; i < N; i++) result[i] /= N;

    free(even);
    free(odd);
    return result;
}


void gp_export_fft(const char *file_path, const complex _Float64 *array, size_t nb_points, uint32_t frequency_sampler) {

    FILE *export = fopen(file_path, "w");

    fprintf(export, "frequency,amplitude\n");
    for (uint32_t i = 0; i < nb_points; i++)
        fprintf(export, "%f,%f\n", i * (_Float64)(frequency_sampler / nb_points), cabs(array[i]));
    
    fclose(export);
    return;
}
