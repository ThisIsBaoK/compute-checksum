# Makefile for compiling a simple C++ program with Clang and C++20

# Compiler and compiler flags
CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra

# Executable name
EXECUTABLE = checksum.exe

# Source files and object files
SOURCES = checksum.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXECUTABLE)
	$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

vet:
	clang-tidy checksum.cpp --use-color -header-filter=.* \
		-- \
		-I. \
		$(CXXFLAGS)

fmt:
	clang-format -i *.cpp

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
