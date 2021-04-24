#ifndef CHIPPY_GUI_H
#define CHIPPY_GUI_H

#include <stdbool.h>
#include "SDL.h"

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
} Gui;

void InitGui(Gui* gui, const char* title, int width, int height, int twidth, int theight);
void DestroyGui(Gui* gui);
void UpdateGui(Gui* gui, void const* buffer, int pitch);
bool ProcessInput(uint8_t* keys);

#endif

