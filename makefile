# Define compiler and compiler flags
CXX = g++
CXXFLAGS = -Wall -Wextra

# Define target executable
TARGET = main

# Define source files and corresponding object files
SRCDIR = src
OBJDIR = obj
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Default rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Rule to clean up object files and executable
clean:
	rm -f $(OBJS) $(TARGET)

