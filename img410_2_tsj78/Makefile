CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
LIBS = -lm

SRC_DIR = src
INC_DIR = include
TEST_DIR = tests
BUILD_DIR = build

TARGET = v3test

all: $(TARGET)

$(TARGET): $(BUILD_DIR)/v3math.o $(BUILD_DIR)/v3test.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BUILD_DIR)/v3math.o: $(SRC_DIR)/v3math.c $(INC_DIR)/v3math.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/v3test.o: $(TEST_DIR)/v3test.c $(INC_DIR)/v3math.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)