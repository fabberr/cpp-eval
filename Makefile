.DEFAULT_GOAL := $(OUTPUT)

################################################################################
#                                  VARIABLES                                   #
################################################################################

PROJECT := cpp-eval

INCLUDE_DIRECTORY := ./include
SOURCE_DIRECTORY := ./src
BUILD_DIRECTORY := ./build

################################################################################
#                                 COMPILATION                                  #
################################################################################

CXX := g++
CXX_WARNINGS := -Werror -Wall -Wextra -Wshadow -Wconversion -Wpedantic
CXX_STANDARD := -std=c++26
CXX_OPTIMIZATION := -O3
CXXFLAGS := $(CXX_WARNINGS) $(CXX_STANDARD) $(CXX_OPTIMIZATION)
CPPFLAGS := -I$(INCLUDE_DIRECTORY)

################################################################################
#                                    FILES                                     #
################################################################################

SOURCES := $(wildcard $(SOURCE_DIRECTORY)/*.cpp)
OBJECTS := $(patsubst $(SOURCE_DIRECTORY)/%.cpp, $(BUILD_DIRECTORY)/%.o, $(SOURCES))
OUTPUT := $(BUILD_DIRECTORY)/$(PROJECT)

################################################################################
#                                   TARGETS                                    #
################################################################################

# Builds the final executable by linking all the object files
$(OUTPUT): $(OBJECTS) | $(BUILD_DIRECTORY)
	$(CXX) -o $(OUTPUT) $(OBJECTS)

# Compiles all the source files into object files
$(BUILD_DIRECTORY)/%.o: $(SOURCE_DIRECTORY)/%.cpp | $(BUILD_DIRECTORY)
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

# Ensures the output directory exists
$(BUILD_DIRECTORY):
	mkdir -p $(BUILD_DIRECTORY)

# Invokes the executable
.PHONY: run
run: $(OUTPUT)
	$(OUTPUT)

# Cleans the output directory
.PHONY: clean
clean:
	rm -rf $(BUILD_DIRECTORY)
