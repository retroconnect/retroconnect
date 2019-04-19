# Build directory
BUILD_DIR := build

# The name of the project
TARGET := retroconnect

# compiler options for C++
CXXFLAGS := -Wall -Wpedantic -O2 -std=gnu++14

# additional libraries to link
LIBS =

# names for the compiler programs
CXX = g++

# Source Destinations
SRC_DIRS := src/Mapping/ControllerConverters/

# Includes Directories
INCLUDES := -I src/Mapping/ControllerConverters/ -I src/Mapping/ControllerModels/

# automatically create lists of the sources and objects
SRC_FILES := $(wildcard $(addsuffix *.cpp, $(SRC_DIRS)))
OBJS := $(SRC_FILES:%.cpp=$(BUILD_DIR)/%.o)

# the actual makefile rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $(LIBS) $(CXXFLAGS) $(INCLUDES) $^

$(OBJS): $(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(TARGET) $(BUILD_DIR)

.PHONY: clean
