//SDL implementation
#ifndef CONTROLS_H
#define CONTROLS_H

#include "display.h"

#include <SDL2/SDL.h>
#include <vector>
#include "window.h"

void controls_spacebar(std::vector<SDL_Surface*> textSurfaces, console Console, screen Screen);


#endif