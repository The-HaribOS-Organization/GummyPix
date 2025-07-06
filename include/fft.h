#ifndef _FFT_H
#define _FFT_H


#include <stdint.h>
#include <complex.h>


complex _Float64 *gp_fft(complex _Float64 *array, uint32_t N);
complex _Float64 *gp_ifft(complex _Float64 *array, uint32_t N);
void gp_export_fft(const char *file_path, const complex _Float64 *array, size_t nb_points, uint32_t frequency_sampler);

#endif
