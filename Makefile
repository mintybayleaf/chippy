# Makefile for project commands

BUILD_TYPE := Debug
TARGET := run-emu
GENERATOR_NAME=Unix Makefiles 

build:
	cmake -H. -Bbuild -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -G$(GENERATOR_NAME)

.PHONY: build-emu
build-emu: build
	cmake --build build --target chippy-emu

.PHONY: build-dis
build-dis: build
	cmake --build build --target chippy-dis

.PHONY: run-emu
run-emu:  build-emu
	cmake --build build --target run-emu

.PHONY: run-dis
run-dis:  build-dis
	cmake --build build --target run-dis

.PHONY: clean
clean:
	rm -rf build
