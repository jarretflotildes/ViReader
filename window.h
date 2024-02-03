#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL_ttf.h>

class Window{
    public: 
        SDL_Window *sdlWindow;

        Window();               // default 1200 x 720
        Window(int mode);
        SDL_Window *getSDLWindow();

        void setCurrentScaleMode(int mode);
        void shutdown_Window();

        int getHeight();  
        int getWidth();
        void setMode(int mode);

    private:
        int currentScaleMode;
        int width;
        int height;
        void setHeight(int mode);
        void setWidth(int mode);

};

#endif