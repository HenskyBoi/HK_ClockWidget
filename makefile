# Compiler
CXX = gcc
# Compiler flags
CXXFLAGS = -mwindows -municode -static
# Libraries
LIBS =
# Source files
SRCS = HK_ClockWidget.c
# Output executable
TARGET = HK_ClockWidget.exe

# Build target
$(TARGET): $(SRCS)
	$(CXX) $(SRCS) $(CXXFLAGS) -o $(TARGET) $(LIBS)

# Clean target
clean:
	rm -f $(TARGET)
