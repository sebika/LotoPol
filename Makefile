DEPTH = 5

CC = g++
CFLAGS = -Wall -O3 -g

SOURCES = main.cpp utils.cpp tree.cpp
EXECUTABLE = exec
INCLPATHS = include
OBJECTS = $(SOURCES:.c=.o)

build: $(OBJECTS)
	$(CC) $^ -o $(EXECUTABLE) $(CFLAGS)

createTree: build
	./exec create $(DEPTH)

updateTree: build
	./exec update $(DEPTH)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -rf $(EXECUTABLE)

.PHONY: clean build run
