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

//text settings
typedef struct {
    TTF_Font *font;
    Uint8 fontSize;
    SDL_Color fontColor;
} text;

//Screen
typedef struct{
   SDL_Renderer *renderer;
   SDL_Texture  *text;
   SDL_Surface  *surface;
} screen;

//Console
typedef struct{
   SDL_Surface *surfaceConsole;
   SDL_Texture *textureMessage;
   SDL_Rect consoleRect; //rect where text displayed
} console; 

int WindowWidth;
int WindowHeight;
SDL_Window *Window;

text Text;
screen Screen;
console Console;

void initialize_display(){

    initialize_window();

    initialize_screen();

    initialize_text();

    initialize_console();

}

void initialize_window(){
    WindowWidth = 1200;
    WindowHeight = 800;

    SDL_Init(SDL_INIT_EVERYTHING);
    Window = SDL_CreateWindow("ViReader",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              WindowWidth,
                              WindowHeight,
                              SDL_WINDOW_ALLOW_HIGHDPI);
    if(Window == NULL){
        std::cout << "Could not create window!" << SDL_GetError() << std::endl;
        exit(1);
    }
}

void initialize_screen(){
    //Graphics card does rendering
    Screen.renderer = SDL_CreateRenderer(Window, 
                                             -1,
                                             SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 
}

void initialize_text(){
   //Text Color for System
   Text.font = NULL;
   //White text
   Text.fontColor.r = 255; 
   Text.fontColor.g = 255; 
   Text.fontColor.b = 255;
   //TODO Adjust fontsize based on screen resolution
   Text.fontSize = 72;

   if (TTF_Init() < 0) {
      printf("error initializing SDL_ttf: %s\n", TTF_GetError());
      exit(-1);
   }

   // Load font file
   #ifdef __linux__
   Text.font = TTF_OpenFont("/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf", Text.fontSize);
   #elif __APPLE__
   Text.font = TTF_OpenFont("/Library/Fonts/Arial.ttf", Text.fontSize);
   #elif _WIN32
   Text.font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", Text.fontSize);
   #endif
	
   if (Text.font == NULL) { 
      printf("error loading font file: %s\n", TTF_GetError());
      exit(-1);
   }

}

void initialize_console(){
   Console.surfaceConsole = TTF_RenderText_Solid(Text.font, 
                                                "put your text here", 
                                                   Text.fontColor); 
   Console.textureMessage = SDL_CreateTextureFromSurface(Screen.renderer, Console.surfaceConsole);

   Console.consoleRect.x = 0;  //controls the rect's x coordinate 
   Console.consoleRect.y = 0; // controls the rect's y coordinte
   Console.consoleRect.w = WindowWidth; // controls the width of the rect
   Console.consoleRect.h = WindowHeight; // controls the height of the rect

   SDL_RenderCopy(Screen.renderer, Console.textureMessage, NULL, &Console.consoleRect);
}

/*
 * Main loop of program
 */
void display_driver(){
   SDL_Event winEvent;
   bool running = true;

  //Show 
   SDL_RenderPresent(Screen.renderer);

    //Draw Text
   SDL_CreateTexture(Screen.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 640, 480);
   //Main Driver
   while (running){

        while(SDL_PollEvent(&winEvent) == 0){
             if(winEvent.type == SDL_QUIT){
                   running = false;
                   break;
             }
    	}

        SDL_RenderPresent(Screen.renderer);

    }

}

void display_shutdown(){
   //Font
   TTF_Quit();

   //Screen
   SDL_DestroyRenderer(Screen.renderer);

   //Window
   SDL_DestroyWindow(Window);

   //Console
   SDL_FreeSurface(Console.surfaceConsole);
   SDL_DestroyTexture(Console.textureMessage);

   SDL_Quit();
}

