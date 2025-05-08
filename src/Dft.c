#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include "Dft.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Function to compute the DFT of a signal
Complex* compute_DFT(const double* input, int N) {
    Complex* output = (Complex*)malloc(N * sizeof(Complex));

    if (!output) {
        perror("Failed to allocate memory for DFT output");
        exit(1);
    }

    for (int k = 0; k < N; k++) {
        output[k].real = 0.0;
        output[k].imag = 0.0;
        for (int n = 0; n < N; n++) {
            double angle = 2 * M_PI * k * n / N;
            output[k].real += input[n] * cos(angle); // Real part
            output[k].imag -= input[n] * sin(angle); // Imaginary part (negative due to the formula)
        }
    }

    return output;
}

// Function to print the DFT (for debugging)
void print_DFT(Complex* in, int N) {
    for (int i = 0; i < N; i++) {
        printf("DFT[%d]: %.5f + %.5fi\n", i, in[i].real, in[i].imag);
    }
}

// Function to read a signal (waveform) from a text file
double* read_signal_from_file(const char* filename, int* out_length) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(1);
    }

    int length = 0;
    while (fscanf(file, "%*f %*f") != EOF) {
        length++;
    }

    fseek(file, 0, SEEK_SET); // Go back to the start of the file

    double* signal = (double*)malloc(length * sizeof(double));
    if (!signal) {
        perror("Failed to allocate memory for signal");
        exit(1);
    }

    int i = 0;
    while (fscanf(file, "%lf", &signal[i]) != EOF) {
        i++;
    }

    fclose(file);

    *out_length = length;
    return signal;
}

// Function to write the DFT results to a file
void write_DFT_on_file(double* data, int N, const char *filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file");
        exit(1);
    }

    for (int i = 0; i < N; i++) {
        fprintf(file, "%d %.5f\n", i, data[i]);
    }

    fclose(file);
}
