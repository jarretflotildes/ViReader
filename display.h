//SDL implementation
#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <SDL_ttf.h>

//text settings
typedef struct {
    TTF_Font *font;
    Uint8 fontSize;
    SDL_Color fontColor;
} text;

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
void initialize_text();
void initialize_console();

//updaters
void update_screen();
void update_console();

//getters
int getWindowWidth();
int getWindowHeight();
SDL_Window *getWindow();
text getText();
screen getScreen();
console getConsole();

void display_shutdown();

#endif