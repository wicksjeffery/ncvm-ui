CXX = c++
CXXFLAGS = -std=c++20 -fmodules-ts -lncurses


SOURCES := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))
DEPENDS := $(patsubst %.cpp,%.d,$(SOURCES))
AOUT := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))bin/ncvm

WARNING := -Wall -Wextra

# .PHONY: all clean

all: ncvm-test1

clean:
	$(RM) $(OBJECTS) $(DEPENDS) ncvm-test1

# Linking the executable from the object files
ncvm-test1: $(OBJECTS)
	$(CXX) $(WARNING) $(CXXFLAGS) $^ -o $(AOUT)

# -include $(DEPENDS)

%.o: %.cpp Makefile
	$(CXX) $(WARNING) $(CXXFLAGS) -MMD -MP -c $< -o $@

