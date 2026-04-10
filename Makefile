CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11
SRC_DIR = src
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
TARGET = $(BUILD_DIR)/huffman

.PHONY: all clean run watch

all: $(TARGET)

$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

run: $(TARGET)
	@./$(TARGET)

watch:
	@echo "Watching $(SRC_DIR)/ for changes..."
	@fswatch -l 0.5 -o $(SRC_DIR) | while read -r _; do \
		clear; \
		echo "Rebuilding..."; \
		if $(MAKE) --no-print-directory all; then \
			clear; \
			./$(TARGET); \
		fi; \
	done

clean:
	rm -rf $(BUILD_DIR)
