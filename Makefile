# Makefile for project commands

BUILD_TYPE := Debug
GENERATOR_NAME := "Unix Makefiles"
INSTALL_PREFIX := /usr


.PHONY: all
all: build

gen:
	cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DCMAKE_INSTALL_PREFIX=$(INSTALL_PREFIX) -G$(GENERATOR_NAME)

.PHONY: build
build: gen
	cmake --build build --target chippy

.PHONY: opcode_test
opcode_test: build
	./build/bin/chippy 10 1 ./roms/BC_test.ch8

.PHONY: tetris
tetris: build
	./build/bin/chippy 10 3 ./roms/Tetris.ch8

.PHONY: install
install: build
	cmake --build build --target install

.PHONY: clean
clean:
	rm -rf build
	rm -f CMakeCache.txt
	rm -rf CMakeFiles
