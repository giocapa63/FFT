#ifndef WAVEFORMS_H
#define WAVEFORMS_H

typedef double (*waveform_func)(double t, double frequency);

// Structure to hold information for each waveform
typedef struct {
    const char *name;          // Name of the waveform (e.g., "sine", "square")
    waveform_func func;        // Function pointer to the waveform generator
    const char *txt_filename;  // Filename for the txt output
    const char *dft_filename;  // Filename for the txt dft output
} waveform_info;

// Declare waveform generator functions
double sineFunction(double t, double frequency);
double squaredFunction(double t, double frequency);

// Accessors
waveform_info get_waveform_info(const char *type);

#endif
