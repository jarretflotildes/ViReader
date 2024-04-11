#ifndef MENUITEM_H
#define MENUITEM_H

#include <SDL2/SDL.h>
#include <SDL_ttf.h>

#include <string.h>

class MenuItem{
    public: 
       MenuItem(std::string label,TTF_Font *font);
       SDL_Surface *getSurface();

    private:
       SDL_Texture  *text;
       SDL_Surface  *surface;

};

#endif