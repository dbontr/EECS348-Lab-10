CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -O2
INCLUDE := -Isrc
BUILD_DIR := build
BIN_DIR := bin
TARGET := $(BIN_DIR)/string_calc


SRC := $(wildcard src/*.cpp)
OBJ := $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(SRC))


.PHONY: all clean run


all: $(TARGET)


$(TARGET): $(OBJ)
@mkdir -p $(BIN_DIR)
$(CXX) $(CXXFLAGS) $^ -o $@


$(BUILD_DIR)/%.o: src/%.cpp src/%.hpp
@mkdir -p $(BUILD_DIR)
$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@


run: all
$(TARGET) tests/testcases.txt


clean:
rm -rf $(BUILD_DIR) $(BIN_DIR)
