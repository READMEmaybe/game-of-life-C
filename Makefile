CC ?= cc
CFLAGS ?= -std=c17 -Wall -Wextra -Wpedantic -O2
SDL_CFLAGS := $(shell pkg-config --cflags sdl2)
SDL_LIBS := $(shell pkg-config --libs sdl2)

TARGET := game-of-life
SOURCES := main.c utils.c

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCES) gameOfLife.h
	$(CC) $(CFLAGS) $(SDL_CFLAGS) $(SOURCES) $(SDL_LIBS) -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
