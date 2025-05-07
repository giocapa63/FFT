#ifndef WARHEADER_H
#define WARHEADER_H

#include <stdio.h>   // For FILE
#include <stdint.h>  // For uint32_t

void write_wav_header(FILE *f, int num_samples, uint32_t sample_rate);


#endif //WARHEADER_H

