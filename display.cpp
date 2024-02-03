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
#include "window.h"

Window gWindow;

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
   gWindow = Window();
}

void initialize_screen(){
    //Graphics card does rendering
    Screen.renderer = SDL_CreateRenderer(gWindow.window, 
                                             -1,
                                             SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 
    //Show 
    SDL_RenderPresent(Screen.renderer);

    //Draw Text
    SDL_CreateTexture(Screen.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 640, 480);

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
   int width = gWindow.getWidth();
   int height = gWindow.getHeight();

   int console_width =  (int)(0.85 * width);
   int console_height = (int)(0.85 * height);

   // calculate the position of the top-left corner of the rectangle
   int console_x = (int)((width - console_width) / 2);
   int console_y = (int)((height - console_height) / 2);

   // set console location
   Console.consoleRect.x = console_x;    Console.consoleRect.y = console_y;
   Console.consoleRect.w = console_width; Console.consoleRect.h = console_height;
}

void update_screen(){
   //Clear Screen
   SDL_RenderClear(Screen.renderer);
   //Console
   SDL_SetRenderDrawColor(Screen.renderer, 30, 30, 30, 140);
   SDL_RenderFillRect(Screen.renderer, &Console.consoleRect); 
   //Text
   SDL_RenderCopy(Screen.renderer,Screen.text,NULL,&Console.consoleRect);
   //Show
   SDL_RenderPresent(Screen.renderer);
}

Window display_getWindow(){
   return gWindow;
}

text display_getText(){
   return Text;
}

screen display_getScreen(){
   return Screen;
}

console display_getConsole(){
   return Console;
}

void display_shutdown(){
   //Font
   TTF_Quit();

   //Screen
   SDL_DestroyRenderer(Screen.renderer);

   //Window
   gWindow.shutdown_Window();

   //Console
   SDL_FreeSurface(Console.surfaceConsole);
   SDL_DestroyTexture(Console.textureMessage);

   SDL_Quit();
}

