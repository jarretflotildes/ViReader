#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <iostream>

#include "window.h"

/* Mode 0: 1200 x 720

*/

Window::Window(){
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("ViReader",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              1200,
                              720,
                              SDL_WINDOW_ALLOW_HIGHDPI);

    currentScaleMode = 0;

    if(window == NULL){
        std::cout << "Could not create window!" << SDL_GetError() << std::endl;
        exit(1);
    }

}

Window::Window(int mode){
    SDL_Init(SDL_INIT_EVERYTHING);

    currentScaleMode = mode;
    setHeight(mode);
    setWidth(mode);

    window = SDL_CreateWindow("ViReader",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width,
                              height,
                              SDL_WINDOW_ALLOW_HIGHDPI);

    if(window == NULL){
        std::cout << "Could not create window!" << SDL_GetError() << std::endl;
        exit(1);
    }
}


int Window::getHeight(){
    return height;
}

int Window::getWidth(){
    return width;
}

void Window::setHeight(int mode){

    switch(mode) {
        case 0: 
            height = 720;
            break;

        default: 
            height = 720;
            currentScaleMode = 0;
            break;
    }

}

void Window::setWidth(int mode){

    switch (mode){
        case 0: 
            width = 1200;
            break;
    
        default:
            width = 1200;
            currentScaleMode = 0;
            break;
    }

}

void Window::setCurrentScaleMode(int mode){
    currentScaleMode = mode;
    setWidth(mode);
    setHeight(mode);
    SDL_SetWindowSize(window,width,height);
}

void Window::shutdown_Window(){
    SDL_DestroyWindow(window);
}
