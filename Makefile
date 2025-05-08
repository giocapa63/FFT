CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm
SRC_DIR = src
BUILD_DIR = build

# File comuni
COMMON_OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/Dft.o $(BUILD_DIR)/waveforms.o $(BUILD_DIR)/wavheader.o

# Target executable
TARGET = $(BUILD_DIR)/wavegen

# Default target
all: $(TARGET)

$(TARGET): $(COMMON_OBJS)
	$(CC) $(CFLAGS) $(COMMON_OBJS) -o $(TARGET) $(LDFLAGS)

# Compile object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create the build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean
clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

.PHONY: all clean
