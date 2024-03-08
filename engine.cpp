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

#include "parse.h"

using std::vector;
using std::cout;
using std::endl;

#define TITLESCREEN 0
#define MAINSCREEN 1
#define SETTINGSCREEN 2

/*
 * Main loop of program
 */
void engine_driver(WindowManager *window){
   SDL_Event winEvent;
   bool running = true;

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
   SDL_CreateTexture(Screen.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,window->getWidth(),window->getHeight());
   //Show
   SDL_RenderPresent(Screen.renderer);

   display_MainScreen(window);

   //Main Driver
   while (running){
      while(SDL_PollEvent(&winEvent)){
         if(winEvent.type == SDL_QUIT){
            running = false;
            break;
         } else if(winEvent.type == SDL_KEYDOWN){
                  switch(winEvent.key.keysym.sym){
	                  case SDLK_SPACE:
                     case SDLK_RIGHT:
                     case SDLK_z:
                     case SDLK_x:
                     case SDLK_KP_ENTER:
                        if(display_getCurrentScreenIndex() == MAINSCREEN){ 
                           display_MainScreen_ScrollTextForward(window);
                        } 
                   		break;
                     case SDLK_LEFT:
                        if(display_getCurrentScreenIndex() == MAINSCREEN){
                           display_MainScreen_ScrollTextBackward(window);
                        }
                     default:
		                  break;
    	      }

         }
      }
   }
   
}
