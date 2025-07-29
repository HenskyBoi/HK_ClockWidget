# Compiler
CXX = gcc
# Compiler flags
CXXFLAGS = -mwindows -municode -static
# Libraries
LIBS =
# Source files
SRCS = hellowin.c
# Output executable
TARGET = win.exe

# Build target
$(TARGET): $(SRCS)
	$(CXX) $(SRCS) $(CXXFLAGS) -o $(TARGET) $(LIBS)

# Clean target
clean:
	rm -f $(TARGET)