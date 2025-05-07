CXX = c++
CXXFLAGS = -std=c++20 -fmodules-ts -lncurses


SOURCES := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))
DEPENDS := $(patsubst %.cpp,%.d,$(SOURCES))

# ADD MORE WARNINGS!
WARNING := -Wall -Wextra

# .PHONY means these rules get executed even if
# files of those names exist.
.PHONY: all clean

# The first rule is the default, ie. "make",
# "make all" and "make parking" mean the same
all: ncvm-interface

deploy: ncvm-interface
	ssh virtman@192.168.122.1 'killall -q ncvm-interface; exit 0'
	scp ncvm-interface virtman@192.168.122.1:~/bin/

clean:
	$(RM) $(OBJECTS) $(DEPENDS) ncvm-interface

# Linking the executable from the object files
ncvm-interface: $(OBJECTS)
	$(CXX) $(WARNING) $(CXXFLAGS) $^ -o $@

-include $(DEPENDS)

%.o: %.cpp Makefile
	$(CXX) $(WARNING) $(CXXFLAGS) -MMD -MP -c $< -o $@

