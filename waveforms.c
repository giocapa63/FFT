#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>
#include <stddef.h>

#include "waveforms.h"  // Make sure this is included to match the struct

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Waveform function definitions
double sineFunction(double t, double freq) {
    return sin(2 * M_PI * freq * t);
}

double squaredFunction(double t, double freq) {
    return (sin(2 * M_PI * freq * t) > 0.0) ? 1.0 : -1.0;
}

// Array of waveform info
static waveform_info waveforms[] = {
        {"sine", sineFunction, "sine.txt", "sineDFT.txt"},
        {"square", squaredFunction, "square.txt", "squareDFT.txt"}
};

#define NUM_WAVEFORMS (sizeof(waveforms) / sizeof(waveform_info))


waveform_info get_waveform_info(const char *type) {
    for (size_t i = 0; i < NUM_WAVEFORMS; i++) {
        if (strcmp(waveforms[i].name, type) == 0) {
            return waveforms[i];
        }
    }
    waveform_info empty = {NULL, NULL, NULL, NULL};
    return empty;
}
