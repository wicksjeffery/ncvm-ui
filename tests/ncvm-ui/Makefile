CXX = c++
CXXFLAGS = -std=c++20 -O2 -fmodules-ts -lncurses -lpanel
OBJDIR = obj
TARGET = bin/ncvm-ui
SOURCES := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp,$(OBJDIR)/%.o,$(SOURCES))
HEADERS := $(wildcard *.hpp)
# AOUT := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))bin/ncvm

DEBUG	:= -Wall -Wextra -g

# .PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(OBJECTS) $(DEPENDS) $(TARGET)

# Link the executable from the object files
$(TARGET): $(OBJECTS)
	$(CXX) $(WARNING) $(CXXFLAGS) $^ -o $(TARGET)

$(OBJDIR)/%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

debug: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(DEBUG) -o $(TARGET)_debug $^

test: $(TARGET)
	./testui.sh -t

