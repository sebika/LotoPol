CC = g++
CFLAGS = -Wall -O3

SOURCES = main.cpp utils.cpp tree.cpp
EXECUTABLE = exec
INCLPATHS = include
OBJECTS = $(SOURCES:.c=.o)

build: $(OBJECTS)
	$(CC) $^ -o exec $(CFLAGS)

run: exec
	./exec

clean:
	rm -rf $(EXECUTABLE)

.PHONY: clean build run
