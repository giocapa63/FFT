#include "math.h"
#include "Dft.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

// Function to compute the Discrete Fourier Transform (DFT) of a given signal
Complex* compute_DFT(const double* input, int N) {
    Complex* output = malloc(N * sizeof(Complex));
    if (!output) {
        return NULL;  // Allocation failed
    }

    for (int k = 0; k < N; ++k) {
        output[k].real = 0.0;
        output[k].imag = 0.0;
        for (int n = 0; n < N; ++n) {
            double angle = -2.0 * M_PI * k * n / N;
            output[k].real += input[n] * cos(angle);
            output[k].imag += input[n] * sin(angle);
        }
    }

    return output;
}

// Function to print the DFT results
void print_DFT(Complex *in, int N) {
    for (int i = 0; i < N; i++) {
        printf("%f + %fi\n", in[i].real, in[i].imag);
    }
}

// Function to read signal from file and return its data in a dynamically allocated array
double* read_signal_from_file(const char* filename, int* out_length) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open input file");
        *out_length = 0;
        return NULL;
    }

    // Count how many numbers are in the file
    int count = 0;
    double tmp;
    while (fscanf(file, "%lf", &tmp) == 1) {
        count++;
    }

    rewind(file);  // Reset file pointer

    double* data = malloc(count * sizeof(double));
    if (!data) {
        perror("Memory allocation failed");
        fclose(file);
        *out_length = 0;
        return NULL;
    }

    // Read data into the array
    for (int i = 0; i < count; ++i) {
        if (fscanf(file, "%lf", &data[i]) != 1) {
            fprintf(stderr, "Unexpected read error at index %d\n", i);
            free(data);
            fclose(file);
            *out_length = 0;
            return NULL;
        }
    }

    fclose(file);
    *out_length = count;
    return data;
}

// Function to write the DFT results to a file
void write_DFT_on_file(double *data, int N, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    // Compute DFT and write results to file
    for (int k = 0; k < N; k++) {
        double real_part = 0.0;
        double imag_part = 0.0;
        for (int n = 0; n < N; n++) {
            double angle = 2 * M_PI * k * n / N;
            real_part += data[n] * cos(angle);
            imag_part -= data[n] * sin(angle);  // Negative for the imaginary part
        }
        fprintf(file, "%f + %fi\n", real_part, imag_part);
    }

    fclose(file);
}
