
#ifndef MAIN_C_DFT_H
#define MAIN_C_DFT_H

typedef struct {
    double real;
    double imag;
} Complex;

Complex compute_DFT(const double *input, int N);
void print_DFT(Complex *in);
double* read_signal_from_file(const char* filename, int* out_length);
void write_DFT_on_file(Complex *in);

#endif //MAIN_C_DFT_H
