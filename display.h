//SDL implementation
#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_ttf.h>
#include <vector>

#include "window.h"
#include "menuItem.h"

typedef struct{
   SDL_Renderer *renderer;
   SDL_Texture  *text;
   SDL_Surface  *surface;
} screen;

typedef struct{
   SDL_Surface *surfaceConsole;
   SDL_Texture *textureMessage;
   SDL_Rect consoleRect;
} console; 

typedef struct{
   SDL_Texture *currentPage;
   SDL_Texture *maxPage;
   SDL_Surface *settings;
} mainScreen_elements;

typedef struct{
   SDL_Texture *inner;
   SDL_Texture *outer;
} TextFormat;


//initializers
void initialize_display(WindowManager *window);
void initialize_background(WindowManager *window);
void initialize_screen(WindowManager *window);
void initialize_console(WindowManager *window);
void initialize_SurfaceText(WindowManager *window);
void initialize_menuItems(WindowManager *window);

//updaters
void update_console();

//getters
screen display_getScreen();
console display_getConsole();
SDL_Texture *display_getBackground();

std::vector<SDL_Surface*> display_getSurfaceText();
int display_getCurrentScreenIndex();

//Setters
void display_setSurfaceTextIndex(int index);

//Rendering Stuff
//Helper functions for screen displaying
void display_RenderBackground();
void display_RenderConsole(WindowManager *window);
void display_RenderMenuItems(WindowManager *window);

//Screen Stuff
void display_MainScreen_RenderText(WindowManager *window);
void display_MainScreen(WindowManager *window);
void display_MainScreen_ScrollTextForward(WindowManager *window);
void display_MainScreen_ScrollTextBackward(WindowManager *window);


//Shutdown
void display_shutdown(WindowManager *window);

#endif