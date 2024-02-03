#include <stdio.h>
#include <stdbool.h>
#include <iostream>

//initializing and shutdown functions
#include <SDL2/SDL.h>

//rendering images and graphics on screen/
#include <SDL2/SDL_image.h>

//for using sdl_delay() functions
#include <SDL2/SDL_timer.h>

#include "engine.h"
#include "display.h"
#include "controls.h"

/*
 * Main loop of program
 */
void engine_driver(){

   SDL_Event winEvent;
   bool running = true;
   console Console = display_getConsole();
   screen Screen = display_getScreen();

   //Main Driver
   while (running){
      while(SDL_PollEvent(&winEvent)){
         if(winEvent.type == SDL_QUIT){
            running = false;
            break;
         } else if(winEvent.type == SDL_KEYDOWN){
                  switch(winEvent.key.keysym.sym){
	                  case SDLK_SPACE:
                        controls_spacebar(Console,Screen);
//SDL_RenderCopy(Screen.renderer, Message, NULL, &Message_rect);
                   		break;
                     default:
		                  break;
    	      }
         }
      }
   }
   
}