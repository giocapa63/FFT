#ifndef DFT_H
#define DFT_H

typedef struct {
    double real;
    double imag;
} Complex;

// Compute the DFT of a real-valued input array of length N.
// Returns a dynamically allocated array of Complex numbers.
// Caller is responsible for freeing the returned array.
Complex* compute_DFT(const double* input, int N);

// Prints the DFT results (for debugging or inspection).
void print_DFT(const Complex* dft_result, int N);

// Reads amplitude values from a text file.
// Returns a dynamically allocated array and sets out_length to the number of values read.
double* read_signal_from_file(const char* filename, int* out_length);

// Writes the DFT result to a file.
// The filename is inferred based on context (e.g., from waveform_info).
void write_DFT_on_file(const Complex* dft_result, int N, const char* filename);

#endif // DFT_H
