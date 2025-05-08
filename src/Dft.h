#ifndef DFT_H
#define DFT_H

#include <stdint.h>  // For int16_t

typedef struct {
    double real;
    double imag;
} Complex;

Complex* compute_DFT(const double* input, int N);
void print_DFT(Complex* in, int N);
double* read_signal_from_file(const char* filename, int* out_length);
void write_DFT_on_file(double* data, int N, const char *filename);

#endif // DFT_H
