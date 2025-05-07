CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm
SRC_DIR = src
BUILD_DIR = build

# File comuni
COMMON_OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/Dft.o $(BUILD_DIR)/waveforms.o $(BUILD_DIR)/wavheader.o

# Targets
all: sine square triangle

sine: $(COMMON_OBJS)
	$(CC) $(CFLAGS) $(COMMON_OBJS) -o $(BUILD_DIR)/sine $(LDFLAGS)

square: $(COMMON_OBJS)
	$(CC) $(CFLAGS) $(COMMON_OBJS) -o $(BUILD_DIR)/square $(LDFLAGS)

triangle: $(COMMON_OBJS)
	$(CC) $(CFLAGS) $(COMMON_OBJS) -o $(BUILD_DIR)/triangle $(LDFLAGS)

# Regole per compilare i .o nella cartella build
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Crea la cartella build se non esiste
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/sine $(BUILD_DIR)/square $(BUILD_DIR)/triangle

.PHONY: all clean sine square triangle
