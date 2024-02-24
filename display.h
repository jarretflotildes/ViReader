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
void initialize_display(WindowManager *window);
void initialize_background(WindowManager *window);
void initialize_screen(WindowManager *window);
void initialize_console(WindowManager *window);
void initialize_SurfaceText(WindowManager *window);

//updaters
void update_console();

//getters
screen display_getScreen();
console display_getConsole();
SDL_Texture *display_getBackground();

std::vector<SDL_Surface*> display_getSurfaceText();
int display_getSurfaceTextIndex();

//Setters
void display_setSurfaceTextIndex(int index);

//Rendering Stuff
//Helper functions for screen displaying
void display_RenderBackground();
void display_RenderConsole(WindowManager *window);

//Screen Stuff
void display_MainScreen_RenderText(WindowManager *window);
void display_MainScreen_ScrollText(WindowManager *window);

//Shutdown
void display_shutdown(WindowManager *window);

#endif