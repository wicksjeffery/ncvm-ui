CXX = c++
CXXFLAGS = -std=c++20 -fmodules-ts -lncurses -lpanel

SOURCES := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))
DEPENDS := $(patsubst %.cpp,%.d,$(SOURCES))
# AOUT := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))bin/ncvm

WARNING := -Wall -Wextra

# .PHONY: all clean

all: ncvm-ui

clean:
	$(RM) $(OBJECTS) $(DEPENDS) ncvm-ui

# Linking the executable from the object files
ncvm-ui: $(OBJECTS)
	$(CXX) $(WARNING) $(CXXFLAGS) $^ -o ncvm-ui

%.o: %.cpp Makefile
	$(CXX) $(WARNING) $(CXXFLAGS) -MMD -MP -c $< -o $@

test: ncvm-ui
	./testui.sh -t

