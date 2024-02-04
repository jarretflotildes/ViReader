//SDL implementation
#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <SDL_ttf.h>

#include "window.h"

//Screen
typedef struct{
   SDL_Renderer *renderer;
   SDL_Texture  *text;
   SDL_Surface  *surface;
} screen;

//Console
typedef struct{
   SDL_Surface *surfaceConsole;
   SDL_Texture *textureMessage;
   SDL_Rect consoleRect; //rect where text displayed
} console; 

//initializers
void initialize_display();
void initialize_window();
void initialize_screen();
void initialize_console();

//updaters
void update_screen();
void update_console();

//getters
WindowManager display_getWindow();
screen display_getScreen();
console display_getConsole();

void display_shutdown();

#endif