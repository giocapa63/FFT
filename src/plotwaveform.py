import matplotlib.pyplot as plt
import sys

if len(sys.argv) != 2:
    print(f"Usage: python3 {sys.argv[0]} filename.txt")
    sys.exit(1)

filename = sys.argv[1]

t = []
a = []

with open(filename, 'r') as f:
    for line in f:
        parts = line.strip().split()
        if len(parts) == 2:
            t.append(float(parts[0]))
            a.append(float(parts[1]))

plt.figure(figsize=(10, 5))
plt.plot(t, a)
plt.xlabel('Time [s]')
plt.ylabel('Amplitude')
plt.title(f'Waveform from {filename}')
plt.grid(True)

# Instead of plt.show(), save the plot to a file
output_image = filename.replace('.txt', '.png')
plt.savefig(output_image)

print(f"Plot saved as {output_image}")
