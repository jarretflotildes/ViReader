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

//The amount of lines of text that should be displayed no matter what screen size
void controls_spacebar(vector<SDL_Surface*> textSurfaces,WindowManager *window,console Console, screen Screen){
    int offset = 0;
    text textSettings = window->getTextSettings();

    SDL_RenderClear(Screen.renderer);
    SDL_DestroyTexture(Screen.text);

    //Display Background
    SDL_RenderCopy(Screen.renderer,display_getBackground(),NULL,NULL);

    //Display Console
    SDL_SetRenderDrawColor(Screen.renderer,  textSettings.backgroundColor.r, 
                                             textSettings.backgroundColor.g, 
                                             textSettings.backgroundColor.b, 
                                             textSettings.backgroundColor.a); //Background color of Console

    SDL_SetRenderDrawBlendMode(Screen.renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(Screen.renderer, &Console.consoleRect); 
    SDL_RenderCopy(Screen.renderer,Screen.text,NULL,&Console.consoleRect);
    SDL_RenderPresent(Screen.renderer);

    //Display Text
    SDL_Rect displayText;

    int xAlign = Console.consoleRect.x/2;
    int yAlign = Console.consoleRect.y/2;

    for(int i = 0;i<window->getDisplayLines();i++){
       int currentIndex = display_getSurfaceTextIndex();
       int text_width = textSurfaces.at(currentIndex)->w;
       int text_height = textSurfaces.at(currentIndex)->h;

       displayText.x = Console.consoleRect.x + xAlign;
       displayText.y = Console.consoleRect.y + yAlign + offset;
       displayText.w = text_width;
       displayText.h = text_height;

  	   Screen.text = SDL_CreateTextureFromSurface(Screen.renderer, textSurfaces.at(currentIndex));

       SDL_RenderCopy(Screen.renderer,Screen.text,NULL,&displayText);
       offset+= window->getTextOffset();
       if(currentIndex+1 >= parse_getNumLines()){
          break;
       }
    }

    SDL_RenderPresent(Screen.renderer);
}

