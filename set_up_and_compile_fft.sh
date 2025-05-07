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

# Create structure (build directory added)
mkdir -p "$SRC_DIR" "$BUILD_DIR" "$OUTPUT_DIR" "$DFT_DIR" "$PLOTS_DIR" "$TXT_DIR" "$WAV_DIR"

# Move source files (if they exist)
mv $FFT_DIR/src/*.c "$SRC_DIR" 2>/dev/null
mv $FFT_DIR/src/*.h "$SRC_DIR" 2>/dev/null
mv $FFT_DIR/plotwaveform.py "$SRC_DIR" 2>/dev/null

# Navigate to src and compile waveforms
cd "$SRC_DIR" || exit 1

# Compile each waveform program
for WAVE in sine square triangle; do
  echo "Compiling $WAVE..."
  gcc -Wall -Wextra -std=c99 -D${WAVE^^}_WAVE main.c waveforms.c wavheader.c Dft.c -o "$BUILD_DIR/$WAVE" -lm
done

# Compile DFT module separately if needed
echo "Compiling DFT module..."
gcc Dft.c -o "$BUILD_DIR/compute_dft" -lm

# Run waveform generators
echo "Generating WAV and TXT files..."
cd "$BUILD_DIR" || exit 1
for WAVE in sine square triangle; do
  ./$WAVE $WAVE "$WAV_DIR/$WAVE.wav" "$TXT_DIR/$WAVE.txt"
done

# Run DFT computations
echo "Computing DFT..."
for WAVE in sine square triangle; do
  ./compute_dft "$TXT_DIR/$WAVE.txt" "$DFT_DIR/${WAVE}_dft.txt"
done

# Plot results
echo "Plotting signals..."
for WAVE in sine square triangle; do
  python3 "$SRC_DIR/plotwaveform.py" "$TXT_DIR/$WAVE.txt" "$PLOTS_DIR/$WAVE.png"
done

echo "✅ All tasks completed successfully!"
