#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL_ttf.h>

//text settings
typedef struct {
    TTF_Font *font;
    Uint8 fontSize;
    SDL_Color fontColor;

    SDL_Color backgroundColor;
} text;

class WindowManager{
    public: 
        SDL_Window *sdlWindow;

        WindowManager();               // default 1200 x 720
        WindowManager(int mode);
        SDL_Window *getSDLWindow();

        void setCurrentScaleMode(int mode);
        void shutdown_Window();

        int getHeight();  
        int getWidth();
        int getDisplayLines();
        text getTextSettings();
        int getTextLimit();
        int getTextOffset();
        int getCurrentPage();

        void setMode(int mode);
        void setFontSize(int size);

    private:
        int currentScaleMode;
        int width;
        int height;
        int displayLines;

        int textCharacterLimit;
        int textHeightOffset;

        text textSettings;

};

#endif