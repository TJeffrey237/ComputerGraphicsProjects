CXX = g++
CXXFLAGS = -Wall -g -std=c++11 -Iinclude

SRC_DIR = src
BUILD_DIR = build
TARGET = blur

OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/ppm.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)