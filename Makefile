CXX = c++
CXXFLAGS = -std=c++20 -fmodules-ts -lncurses


SOURCES := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))
DEPENDS := $(patsubst %.cpp,%.d,$(SOURCES))
AOUT := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))bin/ncvm

WARNING := -Wall -Wextra

# .PHONY: all clean

all: ncvm

clean:
	$(RM) $(OBJECTS) $(DEPENDS) ncvm

# Linking the executable from the object files
ncvm: $(OBJECTS)
	$(CXX) $(WARNING) $(CXXFLAGS) $^ -o $(AOUT)

%.o: %.cpp Makefile
	$(CXX) $(WARNING) $(CXXFLAGS) -MMD -MP -c $< -o $@

test: ncvm
	./emulate-target.sh -t

