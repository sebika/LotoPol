CC = g++
CFLAGS = -O3

SOURCES = main.cpp utils.cpp tree.cpp handler.cpp
EXECUTABLE = exec
INCLPATHS = include
OBJECTS = $(SOURCES:.c=.o)

run: build
	./$(EXECUTABLE)

createTrees: build
	./exec create

updateTrees: build
	./exec update

build: $(OBJECTS)
	$(CC) $^ -o $(EXECUTABLE) $(CFLAGS)

clean:
	rm -rf $(EXECUTABLE)

.PHONY: clean build run
