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
    
	  SDL_DestroyTexture(Screen.text);
   
    int heightOffset = 0;
    SDL_RenderClear(Screen.renderer);

    Console.consoleRect.w = textSurfaces.at(currentIndex)->w;
    Console.consoleRect.h = textSurfaces.at(currentIndex)->h + heightOffset;

  	Screen.text = SDL_CreateTextureFromSurface(Screen.renderer, textSurfaces.at(currentIndex));
    update_screen();
    SDL_RenderCopy(Screen.renderer,Screen.text,NULL,&Console.consoleRect);
    //Show
    SDL_RenderPresent(Screen.renderer);

}