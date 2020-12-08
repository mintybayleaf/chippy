# Makefile for project commands

BUILD_TYPE := Debug
GENERATOR_NAME := "Unix Makefiles" 
INSTALL_PREFIX := /usr

build:
	cmake -H. -Bbuild -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DCMAKE_INSTALL_PREFIX=$(INSTALL_PREFIX) -G$(GENERATOR_NAME)

.PHONY: build-emu
build-emu: build
	cmake --build build --target chippy-emu

.PHONY: run
run:  build-emu
	cmake --build build --target run

.PHONY: install
install: build-emu
	cmake --build build --target install

.PHONY: clean
clean:
	rm -rf build
