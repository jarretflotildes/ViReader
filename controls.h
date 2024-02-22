//SDL implementation
#ifndef CONTROLS_H
#define CONTROLS_H

#include "display.h"
#include "window.h"

#include <SDL2/SDL.h>
#include <vector>

void controls_spacebar(std::vector<SDL_Surface*> textSurfaces, WindowManager *window,console Console, screen Screen);


#endif