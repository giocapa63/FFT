import matplotlib.pyplot as plt
import sys
import os
import math
import numpy as np

if len(sys.argv) != 2:
    print(f"Usage: python3 {sys.argv[0]} filename.txt")
    sys.exit(1)

filename = sys.argv[1]

# Constants from main.c (Replace these with actual values from your program)
sample_rate = 1000  # Example sample rate; adjust accordingly to your main.c value
num_samples = 1000  # Example number of samples; adjust accordingly to your main.c value

# Calculate the frequency resolution (spacing between bins)
frequency_resolution = sample_rate / num_samples

# Extract data (real and imaginary parts of the DFT)
x = []
y_real = []
y_imag = []

with open(filename, 'r') as f:
    for line in f:
        # Remove any unwanted characters
        line = line.strip()
        if 'i' in line:  # Only read lines with complex data
            parts = line.split(' + ')
            if len(parts) == 2:
                real_part, imag_part = parts
                real_part = real_part.replace('i', '')  # Remove the 'i' part
                imag_part = imag_part.replace('i', '')  # Remove the 'i' part
                x.append(len(x))  # Simply increment for bin index (x axis)
                y_real.append(float(real_part))
                y_imag.append(float(imag_part))
                print(f"Reading line: {real_part} + {imag_part}i")

# Compute magnitudes
y_magnitude = [math.sqrt(real**2 + imag**2) for real, imag in zip(y_real, y_imag)]

# Debugging: Print first few values for magnitudes
print(f"First few data points (real, imag):")
for i in range(min(5, len(y_real))):
    print(f"Real: {y_real[i]}, Imag: {y_imag[i]}")

print(f"First few magnitudes:")
for i in range(min(5, len(y_magnitude))):
    print(f"Magnitude {i}: {y_magnitude[i]}")

# If there are any NaN or infinite values, print a warning
if np.any(np.isnan(y_magnitude)) or np.any(np.isinf(y_magnitude)):
    print("Attenzione: valori NaN o infiniti rilevati nelle magnitudini.")

# Plot the DFT result
plt.figure(figsize=(10, 5))

# Plot magnitude (absolute value of the complex numbers)
plt.plot(x, y_magnitude)

# Labeling the plot
plt.xlabel('Frequency Bin')
plt.ylabel('Magnitude')
plt.title(f'DFT from {os.path.basename(filename)}')
plt.grid(True)

# Set the y-axis limits based on the maximum magnitude
plt.ylim(0, max(y_magnitude) * 1.1)

# Save the plot as a PNG file
output_image = f"{os.path.splitext(filename)[0]}.png"
plt.savefig(output_image)

print(f"DFT plot saved as {output_image}")
