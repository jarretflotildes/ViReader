#include <stdio.h>
#include <stdbool.h>
#include <iostream>
#include <vector>

//initializing and shutdown functions
#include <SDL2/SDL.h>

//rendering images and graphics on screen/
#include <SDL2/SDL_image.h>

//for using sdl_delay() functions
#include <SDL2/SDL_timer.h>

#include "engine.h"
#include "display.h"
#include "controls.h"

using std::vector;
using std::cout;
using std::endl;

/*
 * Main loop of program
 */
void engine_driver(){

   SDL_Event winEvent;
   bool running = true;
   console Console = display_getConsole();
   screen Screen = display_getScreen();
   vector<SDL_Surface*> textSurfaces = display_getSurfaceText();

   //Main Driver
   while (running){
      while(SDL_PollEvent(&winEvent)){
         if(winEvent.type == SDL_QUIT){
            running = false;
            break;
         } else if(winEvent.type == SDL_KEYDOWN){
                  switch(winEvent.key.keysym.sym){
	                  case SDLK_SPACE:
                        controls_spacebar(textSurfaces,Console,Screen);
                   		break;
                     default:
		                  break;
    	      }
         }
      }
   }
   
}