#include "stdio.h"
#include "math.h"
#include "stdint.h"
#include "wavheader.h"
#include "waveforms.h"

#define SAMPLE_RATE 44100  // samples per second
#define FREQUENCY   400.0  // frequency in Hertz
#define DURATION    2      // duration of the signal in seconds

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s [sine|square|triangle] output.wav output.txt dftoutput.txt\n", argv[0]);
        return 1;
    }

    // Get the waveform type
    waveform_info wave_info = get_waveform_info(argv[1]);
    if (wave_info.func == NULL) {
        printf("Invalid waveform type. Please use sine, square, or triangle.\n");
        return 1;
    }

    int total_samples = (int)(SAMPLE_RATE * DURATION);

    // Open output WAV file
    FILE *fwav = fopen(argv[2], "wb");
    if (!fwav) {
        perror("Failed to open wav file");
        fclose(fwav);
        return 1;
    }

    // Open output TXT file
    FILE *fp = fopen(argv[3], "w");
    if (!fp) {
        perror("Failed to open txt file");
        fclose(fp);
        return 1;
    }

    // Open dft output TXT file
    FILE *fdft = fopen(argv[4], "w");
    if (!fdft) {
        perror("Failed to open dft file");
        fclose(fdft);
        return 1;
    }

    // Write WAV header
    write_wav_header(fwav, total_samples, SAMPLE_RATE);

    // Generate and write samples
    for (int n = 0; n < total_samples; ++n) {
        double t = (double)n / SAMPLE_RATE;
        double amplitude = wave_info.func(t, FREQUENCY);
        int16_t sample = (int16_t)(amplitude * 32767);

        // Write amplitude data to .txt
        fprintf(fp, "%1f %1f\n", t, amplitude);

        // Write sample data to .wav
        fwrite(&sample, sizeof(int16_t), 1, fwav);
    }

    // Close files
    fclose(fp);
    fclose(fwav);

    // Optionally, write the DFT to the dftoutput.txt file
    double* signal_data = malloc(total_samples * sizeof(double));
    if (signal_data) {
        for (int n = 0; n < total_samples; ++n) {
            signal_data[n] = wave_info.func((double)n / SAMPLE_RATE, FREQUENCY);
        }

        write_DFT_on_file(signal_data, total_samples, argv[4]);
        free(signal_data);
    }

    printf("Success\n");
    return 0;
}
