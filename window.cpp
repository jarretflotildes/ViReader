#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <iostream>

#include "window.h"

using std::cout;
using std::endl;

/* Mode 0: 1200 x 720
   //TODO Implement other window sizes
   Mode 9: Full Screen 

*/
WindowManager::WindowManager(){

    /*Initialize Window */
    currentScaleMode = 0;
    setCurrentScaleMode(0);

    sdlWindow = SDL_CreateWindow("ViReader",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width,
                              height,
                              SDL_WINDOW_ALLOW_HIGHDPI);

    if(sdlWindow == NULL){
        std::cout << "Could not create window!" << SDL_GetError() << std::endl;
        exit(1);
    }

    /* Initialize Text*/
   if (TTF_Init() < 0) {
      printf("error initializing SDL_ttf: %s\n", TTF_GetError());
      exit(-1);
   }

   // Load font file
   textSettings.font = TTF_OpenFont("./FONTS/BIZ-UDGothicB.ttc", textSettings.fontSize);
	
   if (textSettings.font == NULL) { 
      printf("error loading font file: %s\n", TTF_GetError());
      exit(-1);
   }

}

WindowManager::WindowManager(int mode){

    currentScaleMode = mode;
    setCurrentScaleMode(mode);

    /* Initialize Window*/
    sdlWindow = SDL_CreateWindow("ViReader",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width,
                              height,
                              SDL_WINDOW_ALLOW_HIGHDPI);

    if(sdlWindow == NULL){
        std::cout << "Could not create window!" << SDL_GetError() << std::endl;
        exit(1);
    }

   /*Initialize font*/
   if (TTF_Init() < 0) {
      printf("error initializing SDL_ttf: %s\n", TTF_GetError());
      exit(-1);
   }

   // Load font file
   textSettings.font = TTF_OpenFont("./FONTS/BIZ-UDGothicB.ttc", textSettings.fontSize);
	
   if (textSettings.font == NULL) { 
      printf("error loading font file: %s\n", TTF_GetError());
      exit(-1);
   }

}

int WindowManager::getHeight(){
    return height;
}

int WindowManager::getWidth(){
    return width;
}

int WindowManager::getDisplayLines(){
    return displayLines;
}

text WindowManager::getTextSettings(){
    return textSettings;
}

int WindowManager::getTextLimit(){
    return textCharacterLimit;
}

int WindowManager::getTextOffset(){
    return textHeightOffset;
}

void WindowManager::setCurrentScaleMode(int mode){
   currentScaleMode = mode;

   /* Values to set that are the same no matter how large window is */

   //White text
   textSettings.fontColor.r = 255; 
   textSettings.fontColor.g = 255; 
   textSettings.fontColor.b = 255;

   //Console Color
   textSettings.backgroundColor.r = 100;
   textSettings.backgroundColor.g = 140;
   textSettings.backgroundColor.b = 180;
   textSettings.backgroundColor.a = 185;

   /* Window Specific settings */
   switch (mode){
        case 0: 
            width = 1200;
            height = 720;
            textCharacterLimit = 50;
            textHeightOffset = 60;
            displayLines = 10;
            textSettings.fontSize = 40;
            break;
    
        default:
            width = 1200;
            height = 720;
            textCharacterLimit = 50;
            textHeightOffset = 60;
            displayLines = 10;
            textSettings.fontSize = 40;
            currentScaleMode = 0;
            break;
    }

    SDL_SetWindowSize(sdlWindow,width,height);
}

void WindowManager::setFontSize(int size){
    textSettings.fontSize = size;
}

void WindowManager::shutdown_Window(){
    SDL_DestroyWindow(sdlWindow);
    TTF_CloseFont(textSettings.font);
}
