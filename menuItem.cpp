#include <stdio.h>
#include <stdlib.h>

#include <string>

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL_ttf.h>

#include "menuItem.h"
#include "window.h"

using std::string;

  MenuItem::MenuItem(std::string label,TTF_Font *font){
     surface = TTF_RenderText_Solid(font,label.c_str(),(SDL_Color){0,0,0});
  }

  SDL_Surface* MenuItem::getSurface(){
    return surface;
  }
