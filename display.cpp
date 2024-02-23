#include <stdio.h>
#include <stdbool.h>
#include <iostream>
#include <cstring>
#include <vector>

//initializing and shutdown functions
#include <SDL2/SDL.h>

//rendering images and graphics on screen/
#include <SDL2/SDL_image.h>

//for using sdl_delay() functions
#include <SDL2/SDL_timer.h>

//Text
#include <SDL_ttf.h>

#include "display.h"
#include "window.h"
#include "parse.h"

using std::vector;
using std::cout;
using std::endl;

screen Screen;
/* typedef struct{
   SDL_Renderer *renderer;
   SDL_Texture  *text;
   SDL_Surface  *surface;
} screen;
*/
console Console;
/* typedef struct{
   SDL_Surface *surfaceConsole;
   SDL_Texture *textureMessage;
   SDL_Rect consoleRect; //rect where text displayed
} console;
*/
SDL_Texture *Background;
SDL_Rect *TempRectBackground; //Background to display if no background loaded from img

vector<SDL_Surface*> TextSurfaces;
int CurrentText;

void initialize_display(WindowManager *window){
    initialize_screen(window);
    initialize_background(window);
    initialize_console(window);
    initialize_SurfaceText(window);
}

void initialize_screen(WindowManager *window){

    //Graphics card does rendering
    Screen.renderer = SDL_CreateRenderer(window->sdlWindow, 
                                             -1,
                                             SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 

    //Show 
    SDL_RenderPresent(Screen.renderer);

    int width = window->getWidth() * 0.75;
    int height = window->getHeight() * 0.75;

    //Draw Text
    SDL_CreateTexture(Screen.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,width,height);

}

void initialize_background(WindowManager *window){
   SDL_Surface *surface = IMG_Load("img/1.png");
   if(surface == NULL){
      surface = SDL_CreateRGBSurface(0,10,10,10,10,10,10,10);
      SDL_FillRect(surface,TempRectBackground,0);
   }

   if(!(Background = SDL_CreateTextureFromSurface(Screen.renderer,surface))){
      cout << "Failed to make background" << endl;
   }
   //Darken
   SDL_SetTextureColorMod(Background,170,170,170);
   //Set Transparency
   SDL_SetRenderDrawBlendMode(Screen.renderer,SDL_BLENDMODE_BLEND);
   
}

void initialize_console(WindowManager *window){
   int width = window->getWidth();
   int height = window->getHeight();

   int console_width =  (int)(0.90 * width);
   int console_height = (int)(0.90 * height);

   // calculate the position of the top-left corner of the rectangle
   int console_x = (int)((width - console_width) / 2);
   int console_y = (int)((height - console_height) / 2);

   // set console location
   Console.consoleRect.x = console_x;    Console.consoleRect.y = console_y;
   Console.consoleRect.w = console_width; Console.consoleRect.h = console_height;

}

void initialize_SurfaceText(WindowManager *window){

    text Text = window->getTextSettings();

    for(int i = 0;i<parse_getNumLines();i++){
       string line = parse_getText().at(i);
//       SDL_Surface *currentSurface = TTF_RenderText_Blended_Wrapped(Text.font,line.c_str(),(SDL_Color){0,0,0},60); //wraps text around
      SDL_Surface *currentSurface = TTF_RenderText_Solid(Text.font,line.c_str(),(SDL_Color){0,0,0});
       TextSurfaces.push_back(currentSurface);
    }

    CurrentText = 0;

}

screen display_getScreen(){
   return Screen;
}

console display_getConsole(){
   return Console;
}

SDL_Texture *display_getBackground(){
   return Background;
}

vector<SDL_Surface*> display_getSurfaceText(){
    return TextSurfaces;
}

int display_getSurfaceTextIndex(){
   CurrentText++;
   if(CurrentText >= parse_getNumLines()){
      CurrentText = 0;
   }
   return CurrentText;
}

void display_shutdown(WindowManager *window){
   //Font
   TTF_Quit();

   //Screen
   SDL_DestroyRenderer(Screen.renderer);

   //Window
   window->shutdown_Window();

   //Console
   SDL_FreeSurface(Console.surfaceConsole);
   SDL_DestroyTexture(Console.textureMessage);

   //Text
   for(int i = 0;i<parse_getNumLines();i++){
        SDL_FreeSurface(TextSurfaces.at(i));
   }

   SDL_Quit();
}