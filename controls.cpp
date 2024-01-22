#include <stdio.h>
#include <stdbool.h>
#include <iostream>

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

//TEMP STUFF
int Current_surface;

SDL_Surface *Surfaces[3];

void initialize_controls(){
//TEMPORARY
    console Console = display_getConsole();
    text Text = display_getText();

    Current_surface = 0;
   const char* text[] = {"\"...\"","...That's right.","This text display kinda works","If what this says is true then... that means..!"};

   for(int i = 0;i<4;i++){
      Surfaces[i] = TTF_RenderText_Solid(Text.font,text[i],(SDL_Color){0,0,0});
   }

   Console.consoleRect = {Console.consoleRect.x + 10,
               Console.consoleRect.y,Surfaces[0]->w,
               Surfaces[0]->h};

}

void controls_spacebar(console Console, screen Screen){
    Current_surface++;
	if(Current_surface >= 4){
	    Current_surface = 0;	  
	}

	Console.consoleRect.w = Surfaces[Current_surface]->w;
	Console.consoleRect.h = Surfaces[Current_surface]->h;
	SDL_DestroyTexture(Screen.text);
	Screen.text = SDL_CreateTextureFromSurface(Screen.renderer,Surfaces[Current_surface]);
    update_screen();
    SDL_RenderCopy(Screen.renderer,Screen.text,NULL,&Console.consoleRect);
    //Show
    SDL_RenderPresent(Screen.renderer);
}

