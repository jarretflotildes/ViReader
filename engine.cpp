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

int TEMP_iterator;
/*
 * Main loop of program
 */
void engine_driver(){

   SDL_Event winEvent;
   bool running = true;
//XXX 
   const char* text[] = {"\"...\"","...That's right.","This text display kinda works","If what this says is true then... that means..!"};
   SDL_Surface* surfaces[3];

   for(int i = 0;i<4;i++){
      surfaces[i] = TTF_RenderText_Solid(getText().font,text[i],(SDL_Color){0,0,0});
   }

   console Console = getConsole();
   screen Screen = getScreen();

   getConsole().consoleRect = {getConsole().consoleRect.x + 10,
               getConsole().consoleRect.y,surfaces[0]->w,
               surfaces[0]->h};

   int current_surface = 0;
TEMP_iterator++;
   //Main Driver
   while (running){
      while(SDL_PollEvent(&winEvent)){
         if(winEvent.type == SDL_QUIT){
            running = false;
            break;
         } else if(winEvent.type == SDL_KEYDOWN){
                  switch(winEvent.key.keysym.sym){
	                  case SDLK_SPACE:
TEMP_iterator++;
current_surface = TEMP_iterator;
//	                     current_surface++;
		                  if(current_surface >= 4){
		                     current_surface = 0;	  
		                  }
		                  Console.consoleRect.w = surfaces[current_surface]->w;
		                  Console.consoleRect.h = surfaces[current_surface]->h;
		                  SDL_DestroyTexture(Screen.text);
		                  Screen.text = SDL_CreateTextureFromSurface(Screen.renderer,surfaces[current_surface]);
                        update_screen();
                        SDL_RenderCopy(Screen.renderer,Screen.text,NULL,&Console.consoleRect);
                        //Show
                        SDL_RenderPresent(Screen.renderer);
                   		break;
                     default:
		                  break;
    	      }
         }
         SDL_RenderPresent(Screen.renderer);
      }
        
   }
}