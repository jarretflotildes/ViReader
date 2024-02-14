//SDL implementation
#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_ttf.h>
#include <vector>

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
void initialize_SurfaceText();

//updaters
void display_updateScreen();
void update_console();

//getters
WindowManager display_getWindow();
screen display_getScreen();
console display_getConsole();

std::vector<SDL_Surface*> display_getSurfaceText();
int display_getSurfaceTextIndex();

//Shutdown
void display_shutdown();

#endif