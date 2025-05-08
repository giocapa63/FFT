#include "Dft.h"
#include "waveforms.h"
#include "wavheader.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 10000  // Maximum length of the signal

int main(int argc, char *argv[]) {
    if (argc < 5) {
        printf("Usage: %s <waveform_name> <output_wav> <output_txt> <output_dft_txt>\n", argv[0]);
        return 1;
    }

    const char *waveform_type = argv[1];
    const char *wav_file = argv[2];
    const char *txt_file = argv[3];
    const char *dft_file = argv[4];
    printf("DFT file name: %s\n", dft_file);
    
    // Get waveform function info
    waveform_info wave_info = get_waveform_info(waveform_type);
    if (wave_info.func == NULL) {
        printf("Error: Invalid waveform type\n");
        return 1;
    }

    // Generate the waveform and save it to the text file
    FILE *txt_fp = fopen(txt_file, "w");
    if (!txt_fp) {
        printf("Error: Unable to open %s for writing\n", txt_file);
        return 1;
    }

    int num_samples = 1000;  // Example: 1000 samples
    double frequency = 50.0;  // Example: frequency 50Hz
    double sample_rate = 1000.0;  // Example: sample rate of 1kHz
    double time_step = 1.0 / sample_rate;

    for (int i = 0; i < num_samples; ++i) {
        double t = i * time_step;
        double amplitude = wave_info.func(t, frequency);
        fprintf(txt_fp, "%f %f\n", t, amplitude);
    }
    fclose(txt_fp);

    // Now, generate the WAV file
    FILE *wav_fp = fopen(wav_file, "wb");
    if (!wav_fp) {
        printf("Error: Unable to open %s for writing\n", wav_file);
        return 1;
    }
    write_wav_header(wav_fp, num_samples, sample_rate);
    for (int i = 0; i < num_samples; ++i) {
        short sample = (short)(wave_info.func(i * time_step, frequency) * 32767);
        fwrite(&sample, sizeof(short), 1, wav_fp);
    }
    fclose(wav_fp);

    // DFT computation and writing the result
    double *signal = malloc(num_samples * sizeof(double));
    if (!signal) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Read the waveform data into the signal array (assuming it's already written in txt)
    FILE *txt_input_fp = fopen(txt_file, "r");
    for (int i = 0; i < num_samples; ++i) {
        fscanf(txt_input_fp, "%lf", &signal[i]);
    }
    fclose(txt_input_fp);

    // Compute the DFT and write the result to the dft file
    Complex *dft_result = compute_DFT(signal, num_samples);
    FILE *dft_fp = fopen(dft_file, "w");  // Use the dft_file passed as argument directly
    if (!dft_fp) {
        printf("Error opening DFT output file: %s\n", dft_file);
        return 1;
    }
    for (int i = 0; i < num_samples; ++i) {
        fprintf(dft_fp, "%f + %fi\n", dft_result[i].real, dft_result[i].imag);  // Output real and imag as separate columns
    }
    fclose(dft_fp);

    free(signal);
    free(dft_result);
    return 0;
}
