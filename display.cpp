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


WindowManager gWindow;
screen Screen;
console Console;

vector<SDL_Surface*> TextSurfaces;
int CurrentText;

void initialize_display(){
//    initialize_window();
    initialize_screen();
    initialize_console();
    initialize_SurfaceText();
}


/*
void initialize_window(){
//   gWindow = Window(); //Window already initialized at variable declaration
}
*/

void initialize_screen(){
    //Graphics card does rendering
    Screen.renderer = SDL_CreateRenderer(gWindow.sdlWindow, 
                                             -1,
                                             SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 

    //Show 
    SDL_RenderPresent(Screen.renderer);

    int width = gWindow.getWidth() * 0.75;
    int height = gWindow.getHeight() * 0.75;

    //Draw Text
    SDL_CreateTexture(Screen.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,width,height);

}

void initialize_console(){
   int width = gWindow.getWidth();
   int height = gWindow.getHeight();

   int console_width =  (int)(0.90 * width);
   int console_height = (int)(0.90 * height);

   // calculate the position of the top-left corner of the rectangle
   int console_x = (int)((width - console_width) / 2);
   int console_y = (int)((height - console_height) / 2);

   // set console location
   Console.consoleRect.x = console_x;    Console.consoleRect.y = console_y;
   Console.consoleRect.w = console_width; Console.consoleRect.h = console_height;

}

void initialize_SurfaceText(){

    text Text = gWindow.getText();

    for(int i = 0;i<parse_getNumLines();i++){
       string line = parse_getText().at(i);
//       SDL_Surface *currentSurface = TTF_RenderText_Blended_Wrapped(Text.font,line.c_str(),(SDL_Color){0,0,0},60); //wraps text around
       SDL_Surface *currentSurface = TTF_RenderText_Solid(Text.font,line.c_str(),(SDL_Color){0,0,0});
       TextSurfaces.push_back(currentSurface);
    }

    CurrentText = 0;

}

void display_updateScreen(){
   //Clear Screen
   SDL_RenderClear(Screen.renderer);
   //Console
   SDL_SetRenderDrawColor(Screen.renderer, 30, 30, 30, 140);
   SDL_RenderFillRect(Screen.renderer, &Console.consoleRect); 
}

WindowManager display_getWindow(){
   return gWindow;
}


screen display_getScreen(){
   return Screen;
}

console display_getConsole(){
   return Console;
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

void display_shutdown(){
   //Font
   TTF_Quit();

   //Screen
   SDL_DestroyRenderer(Screen.renderer);

   //Window
   gWindow.shutdown_Window();

   //Console
   SDL_FreeSurface(Console.surfaceConsole);
   SDL_DestroyTexture(Console.textureMessage);

   //Text
   for(int i = 0;i<parse_getNumLines();i++){
        SDL_FreeSurface(TextSurfaces.at(i));
   }

   SDL_Quit();
}

