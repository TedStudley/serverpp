# C++ compiler to use for compiling/linking
CC=g++
# Flags for the C++ compiler
CFLAGS=-Wall -c -Iinclude -std=c++1y -fpermissive
# Flags for the C++ linker
LDFLAGS=-Wall -Iinclude -std=c++1y

INCLUDE_DIR=include

SOURCE_DIR=source

SOURCES=$(wildcard $(SOURCE_DIR)/**/*.cpp) $(wildcard $(SOURCE_DIR)/*.cpp) 
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))
EXECUTABLE=server++

all : $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o :
	$(CC) $(CFLAGS) $< -o $@ 

clean :
	rm -rf $(OBJECTS) server
