//SDL implementation
#ifndef DISPLAY_H
#define DISPLAY_H
#include <SDL2/SDL.h>

void initialize_display();
void initialize_window();
void initialize_screen();

void initialize_text();

void initialize_console();

void display_shutdown();
void display_driver();

#endif