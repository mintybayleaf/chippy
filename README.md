[![CircleCI](https://circleci.com/gh/bayleaf1130/chippy.svg?style=svg)](https://circleci.com/gh/bayleaf1130/chippy)

# chippy

My intro into emulator dev with Chip 8!

A chip8 emulator written in C and using SDL2 for rendering.

## Details

Chip8 is an old virtual machine. It has games and a pretty simple instruction set. Thus, its a pretty good start for emulator development.

## Features

Play chip8 roms. No sound yet but thats because im lazy.


## Build from Source

I use CMake as a build system but a Makefile I wrote to automate stuff.

- Requirements
    1. CMake 3.13.4 or greater
    2. You may need libsdl2-dev if you cant build it with my Makefile

```bash
git clone https://github.com/bayleaf1130/chippy.git
```

Using System SDL2 CMake
```bash
make USE_SYSTEM_SDL2=ON
```

Using SDL2 in subdirectory build
```bash
make
```

Install
```
make install
```
