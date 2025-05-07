#inlcude "math.h"
#include "Dft.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"


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

void print_DFT(Complex *in, int N){
    for (int i = 0; i < N; i++) {
        printf("%f, %fi", in[i].real, in[i].imag)
    }
}

double* read_signal_from_file(const char* filename, int* out_length) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open input file");
        *out_length = 0;
        return NULL;
    }

    // First pass: count how many numbers
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


void write_DFT_on_file(Complex *in, char *wave){
	
}
