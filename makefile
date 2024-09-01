# Include path for CFITSIO headers
FITS_INCLUDE_PATH = /usr/local/include/fits/ 

# CFITSIO library flags
LIBS = -L/usr/local/lib -lcfitsio

# Target executable name
TARGET = read_fits

# Compiler
CC = g++
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11 -I$(FITS_INCLUDE_PATH)

# Source files
SRCS = read_fits.cpp

# Object files (derived from source files)
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean

