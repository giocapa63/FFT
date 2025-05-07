CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Minimal source files for testing
SRC = main.c waveforms.c wavheader.c
OBJ = $(SRC:.c=.o)

# Executables for different waveforms
EXECUTABLES = sine square triangle

# Default target to build all executables
all: $(EXECUTABLES)

# Rule for sine executable
sine: CFLAGS += -DSINE_WAVE
sine: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lm  # Add -lm to link the math library

# Rule for square executable
square: CFLAGS += -DSQUARE_WAVE
square: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lm  # Add -lm to link the math library

# Rule for triangle executable
triangle: CFLAGS += -DTRIANGLE_WAVE
triangle: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lm  # Add -lm to link the math library

# Rule for compiling .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Clean rule
clean:
	rm -f $(OBJ) $(EXECUTABLES) *.txt

# Run the program for sine
run_sine:
	./sine sine sine.wav sine.txt

# Run the program for square
run_square:
	./square square square.wav square.txt

# Run the program for triangle
run_triangle:
	./triangle triangle triangle.wav triangle.txt
# Plotting rules
plot_sine:
	python3 plotwaveform.py sine.txt

plot_square:
	python3 plotwaveform.py square.txt

plot_triangle:
	python3 plotwaveform.py triangle.txt
