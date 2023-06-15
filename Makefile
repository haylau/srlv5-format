# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++20 -Wall -Wextra

# Source directory
SRCDIR := src

# Source files
SRCS := $(wildcard $(SRCDIR)/*.cpp)

# Executable
EXEC := srlv5-format

# Default target
all: $(EXEC)

# Linking source files
$(EXEC): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Clean
clean:
	rm -f $(EXEC)