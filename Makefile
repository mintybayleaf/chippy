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

.PHONY: run
run: build
	cmake --build build --target run

.PHONY: install
install: build
	cmake --build build --target install

.PHONY: clean
clean:
	rm -rf build
	rm -f CMakeCache.txt
	rm -rf CMakeFiles
