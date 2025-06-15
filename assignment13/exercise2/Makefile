CFLAGS = -std=gnu11 -Wall -Wextra -lm
CC = gcc

.PHONY: all clean

SRC_FILES := $(wildcard [1-7].c)
BASENAMES := $(basename $(SRC_FILES))

BIN_FILES := $(foreach f,$(BASENAMES),snippet$(f)_O0 snippet$(f)_O3)

all: $(BIN_FILES)

clean:
	$(RM) $(BIN_FILES)

# Pattern rules for building -O0 and -O3 versions
snippet%_O0: %.c
	$(CC) $(CFLAGS) -O0 -o $@ $<

snippet%_O3: %.c
	$(CC) $(CFLAGS) -O3 -o $@ $<
