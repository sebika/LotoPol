DEPTH = 5

CC = g++
CFLAGS = -Wall -O3

SOURCES = main.cpp utils.cpp tree.cpp handler.cpp
EXECUTABLE = exec
INCLPATHS = include
OBJECTS = $(SOURCES:.c=.o)

run: build
	./$(EXECUTABLE)

createTree: build
	./exec create $(DEPTH)

updateTree: build
	./exec update $(DEPTH)

build: $(OBJECTS)
	$(CC) $^ -o $(EXECUTABLE) $(CFLAGS)

clean:
	rm -rf $(EXECUTABLE)

.PHONY: clean build run
