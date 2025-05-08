#!/bin/bash

# Path to the FFT directory
FFT_DIR="."
SRC_DIR="$FFT_DIR/src"
BUILD_DIR="$FFT_DIR/build"
OUTPUT_DIR="$FFT_DIR/output"
DFT_DIR="$OUTPUT_DIR/dft"
PLOTS_DIR="$OUTPUT_DIR/plots"
TXT_DIR="$OUTPUT_DIR/txt"
WAV_DIR="$OUTPUT_DIR/wav"

# Create necessary directories
mkdir -p "$SRC_DIR" "$BUILD_DIR" "$OUTPUT_DIR" "$DFT_DIR" "$PLOTS_DIR" "$TXT_DIR" "$WAV_DIR"

# Move source files (if they exist)
mv $FFT_DIR/src/*.c "$SRC_DIR" 2>/dev/null
mv $FFT_DIR/src/*.h "$SRC_DIR" 2>/dev/null
mv $FFT_DIR/src/plotwaveform.py "$SRC_DIR" 2>/dev/null

# Navigate to root directory and compile the project
cd "$FFT_DIR" || exit 1
echo "Running make to compile the project..."
make

# Generate WAV, TXT, and DFT files for each waveform type
for WAVE in sine square triangle; do
    echo "Generating WAV, TXT, and DFT files for $WAVE..."
    ./build/wavegen $WAVE "$WAV_DIR/$WAVE.wav" "$TXT_DIR/$WAVE.txt" "$DFT_DIR/${WAVE}_dft.txt"

    # Plot waveform
    echo "Plotting waveform for $WAVE..."
    python3 "$SRC_DIR/plotwaveform.py" "$TXT_DIR/$WAVE.txt"
    mv "$TXT_DIR/$WAVE.png" "$PLOTS_DIR/"

    # Plot DFT
    echo "Plotting DFT for $WAVE..."
    python3 "$SRC_DIR/plot_dft.py" "$DFT_DIR/${WAVE}_dft.txt"
    mv "$DFT_DIR/${WAVE}_dft.png" "$PLOTS_DIR/"

    echo "Files generated for $WAVE."
done

echo "✅ All tasks completed successfully!"
