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
#include "window.h"

using std::vector;
using std::cout;
using std::endl;

/*
 * Main loop of program
 */
void engine_driver(WindowManager *window){
   SDL_Event winEvent;
   bool running = true;

   WindowManager gWin = *window;
//   console Console = display_getConsole();
   /*
      typedef struct{
         SDL_Surface *surfaceConsole;
         SDL_Texture *textureMessage;
         SDL_Rect consoleRect; //rect where text displayed
      } console; 

   */

   screen Screen = display_getScreen();
   /*
      typedef struct{
         SDL_Renderer *renderer;
         SDL_Texture  *text;
         SDL_Surface  *surface;
      } screen;
   */

   vector<SDL_Surface*> textSurfaces = display_getSurfaceText();

   //Draw Text
   SDL_CreateTexture(Screen.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,gWin.getWidth(),gWin.getHeight());
   //Show
   SDL_RenderPresent(Screen.renderer);

   display_MainScreen_ScrollText(window); //advance text

   //Main Driver
   while (running){
      while(SDL_PollEvent(&winEvent)){
         if(winEvent.type == SDL_QUIT){
            running = false;
            break;
         } else if(winEvent.type == SDL_KEYDOWN){
                  switch(winEvent.key.keysym.sym){
	                  case SDLK_SPACE:
                        display_MainScreen_ScrollText(window);

                   		break;
                     default:
		                  break;
    	      }
         }
      }
   }
   
}
