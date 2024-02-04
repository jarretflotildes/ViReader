//SDL implementation
#ifndef CONTROLS_H
#define CONTROLS_H

#include "display.h"

#include <SDL2/SDL.h>
#include <vector>
#include "window.h"

void initialize_controls(WindowManager window);
void controls_shutdown();

void controls_spacebar(console Console, screen Screen);

void incrementCurrentText();

#endif