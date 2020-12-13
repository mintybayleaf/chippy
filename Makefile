# Makefile for project commands

BUILD_TYPE := Debug
GENERATOR_NAME := "Unix Makefiles" 
INSTALL_PREFIX := /usr
USE_SYSTEM_SDL2 := OFF
USE_SDL2_STATIC := OFF

.PHONY: all
all: build

gen:
	cmake -H. -Bbuild -DUSE_SYSTEM_SDL2=$(USE_SYSTEM_SDL2) -DUSE_SDL2_STATIC=$(USE_SDL2_STATIC) -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DCMAKE_INSTALL_PREFIX=$(INSTALL_PREFIX) -G$(GENERATOR_NAME)

.PHONY: build
build: gen
	cmake --build build --target chippy

.PHONY: run
run:
	cmake --build build --target run

.PHONY: install
install: build
	cmake --build build --target install

.PHONY: clean
clean:
	rm -rf build
