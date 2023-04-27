
SRC_FILES=flag.c main.c memory.c option.c string.c
OUT_FILE=cr
OPTS=-std=c99 -O -O3 -Wall
DBG_OPTS=--leak-check=full --show-reachable=yes --track-origins=yes -v

default: build run

build:
	gcc -o $(OUT_FILE) $(SRC_FILES) $(OPTS)

install: build
	cp $(OUT_FILE) $(HOME)/bin

debug:
	gcc -o $(OUT_FILE) $(SRC_FILES) $(OPTS) -g
	valgrind $(DBG_OPTS) ./$(OUT_FILE) --command=ls --args="-l"

run:
	./$(OUT_FILE)

clean:
	rm -vi $(OUT_FILE)

