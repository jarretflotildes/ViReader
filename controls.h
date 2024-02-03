//SDL implementation
#ifndef CONTROLS_H
#define CONTROLS_H

#include "display.h"

#include <SDL2/SDL.h>
#include <vector>

void initialize_controls();
void controls_shutdown();

void controls_spacebar(console Console, screen Screen);

void incrementCurrentText();


#endif