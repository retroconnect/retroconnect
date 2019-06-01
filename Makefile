# Build directory
BUILD_DIR := build

# The name of the project
TARGET := retroconnect

# compiler options for C++
CXXFLAGS := -Wall -O2 -std=gnu++14

# additional libraries to link
LIBS = -lwiringPi

# names for the compiler programs
CXX = g++

# Source Destinations
SRC_DIRS := src/Mapping/ControllerConverters/ src/Backend/ ./

# Includes Directories
INCLUDES =  -I src/Mapping/ControllerConverters/include -I src/Mapping/ControllerModels/
INCLUDES += -I src/Backend/include -I ./

# automatically create lists of the sources and objects
SRC_FILES := $(wildcard $(addsuffix *.cpp, $(SRC_DIRS)))
OBJS := $(SRC_FILES:%.cpp=$(BUILD_DIR)/%.o)

# automatically create list of header files
HEADERS := $(wildcard $(addsuffix *.h, $(INCLUDES)))

# the actual makefile rules
all: $(TARGET)

$(TARGET): $(OBJS) $(HEADERS)
	$(CXX) -o $@ $(LIBS) $(CXXFLAGS) $(INCLUDES) $(OBJS)

$(OBJS): $(BUILD_DIR)/%.o: %.cpp $(HEADERS)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	rm -rf $(TARGET) $(BUILD_DIR)

.PHONY: clean
