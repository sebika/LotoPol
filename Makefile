CC = g++
CFLAGS = -Wall -Wextra -g -O3

SOURCES = main.cpp reader.cpp utils.cpp
EXECUTABLE = exec
INCLPATHS = include
OBJECTS = $(SOURCES:.c=.o)

build: $(OBJECTS)
	$(CC) $^ -o exec $(CFLAGS)

run: exec
	./exec

clean:
	rm -rf $(EXECUTABLE)
	rm -rf main.o

.PHONY: clean build run