#include <stdio.h>
#include <stdbool.h>
#include <iostream>
#include <cstring>

//initializing and shutdown functions
#include <SDL2/SDL.h>

//rendering images and graphics on screen/
#include <SDL2/SDL_image.h>

//for using sdl_delay() functions
#include <SDL2/SDL_timer.h>

//Text
#include <SDL_ttf.h>

#include "display.h"
#include "controls.h"
#include "parse.h"

using std::cout;
using std::endl;

void controls_spacebar(vector<SDL_Surface*> textSurfaces, console Console, screen Screen){
    int currentIndex = display_getSurfaceTextIndex();
    int offset = 0;

	  SDL_DestroyTexture(Screen.text);
    SDL_RenderClear(Screen.renderer);

for(int i = 0;i<3;i++){
    int text_width = textSurfaces.at(currentIndex)->w;
    int text_height = textSurfaces.at(currentIndex)->h;

    Console.consoleRect.x = 0;
    Console.consoleRect.y = 0 + offset;
    Console.consoleRect.w = text_width;
    Console.consoleRect.h = text_height;
  	Screen.text = SDL_CreateTextureFromSurface(Screen.renderer, textSurfaces.at(currentIndex));

//    display_updateScreen();
   //Console
   SDL_SetRenderDrawColor(Screen.renderer, 30, 30, 30, 140);
   SDL_RenderFillRect(Screen.renderer, &Console.consoleRect); 

    SDL_RenderCopy(Screen.renderer,Screen.text,NULL,&Console.consoleRect);
currentIndex = display_getSurfaceTextIndex();

offset+= 50;
}
    SDL_RenderPresent(Screen.renderer);

}

