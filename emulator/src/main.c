#include <SDL2/SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "error.h"
#include "rom.h"
#include "gui.h"
#include "chip8.h"

int main(int argc, char** argv) {
    if (argc != 4) {
		error("Usage: chippy <scale> <delay> <rom>\n [ERROR] %s", "Invalid Args");
	}

	int scale = atoi(argv[1]);
	int delay = atoi(argv[2]);
	char const* romname = argv[3];

	// Rom
	Rom* rom = LoadRom(romname);

	// Chip8
	Chip8 chip8;
	Chip8Init(&chip8);
	Chip8LoadRom(&chip8, rom);

	// Gui
	Gui gui;
	InitGui(&gui, rom->name, CHIP8_VIDEO_WIDTH * scale, CHIP8_VIDEO_HEIGHT * scale, CHIP8_VIDEO_WIDTH, CHIP8_VIDEO_HEIGHT);

	bool quit = false;
	int videopitch = sizeof(chip8.video[0] * CHIP8_VIDEO_WIDTH);

	clock_t last_time = clock();

	// Game Loop
	while (!quit) {
		quit = ProcessInput(chip8.keypad);

		clock_t current_time = clock();
		float delta_time = (float)((current_time - last_time ) * 1000) / CLOCKS_PER_SEC;

		if (delta_time > delay) {
			last_time = current_time;
			Chip8Cycle(&chip8);
			UpdateGui(&gui, chip8.video, videopitch);
		}
		
	}

	DestroyRom(&rom);
	DestroyGui(&gui);
	return EXIT_SUCCESS;
}