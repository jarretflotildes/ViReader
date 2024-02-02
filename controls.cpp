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
#include "controls.h"
#include "parse.h"

using std::vector;
using std::cout;
using std::endl;

int CURRENT_TEXT;

vector<SDL_Surface*> Surfaces;

void initialize_controls(){

    text Text = display_getText();

    for(int i = 0;i<parse_getNumLines();i++){
       string line = parse_getText().at(i);
       SDL_Surface *currentSurface = TTF_RenderText_Solid(Text.font,line.c_str(),(SDL_Color){0,0,0});
       Surfaces.push_back(currentSurface);
    }

    CURRENT_TEXT = 0;
    
}

void controls_shutdown(){
    for(int i = 0;i<parse_getNumLines();i++){
        SDL_FreeSurface(Surfaces.at(i));
    }
}

void controls_spacebar(console Console, screen Screen){

	SDL_DestroyTexture(Screen.text);
    incrementCurrentText();
   
    int heightOffset = 0;
SDL_RenderClear(Screen.renderer);
    for(int i = 0;i<2;i++){

    Console.consoleRect.w = Surfaces.at(CURRENT_TEXT)->w;
    Console.consoleRect.h = Surfaces.at(CURRENT_TEXT)->h + heightOffset;

  	Screen.text = SDL_CreateTextureFromSurface(Screen.renderer,Surfaces.at(CURRENT_TEXT));
    update_screen();
SDL_RenderClear(Screen.renderer);
    SDL_RenderCopy(Screen.renderer,Screen.text,NULL,&Console.consoleRect);
    //Show
    SDL_RenderPresent(Screen.renderer);

    incrementCurrentText();
    heightOffset += 50;

    }
}

void incrementCurrentText(){
    CURRENT_TEXT++;
    if(CURRENT_TEXT > parse_getNumLines()){
        CURRENT_TEXT = 0;
    }
}

