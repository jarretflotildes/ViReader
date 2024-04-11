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
#include "window.h"
#include "parse.h"
#include "menuItem.h"

using std::vector;
using std::cout;
using std::endl;

#define TITLESCREEN 0
#define MAINSCREEN 1
#define SETTINGSCREEN 2

#define DIRLEFT 0
#define DIRRIGHT 1

screen Screen;
/* typedef struct{
   SDL_Renderer *renderer;
   SDL_Texture  *text;
   SDL_Surface  *surface;
} screen;
*/

console Console;
/* typedef struct{
   SDL_Surface *surfaceConsole;
   SDL_Texture *textureMessage;
   SDL_Rect consoleRect; //rect where text displayed
} console;
*/

mainScreen_elements MainElements;

SDL_Texture *Background;
SDL_Rect *TempRectBackground; //Background to display if no background loaded from img

vector<SDL_Surface*> TextSurfaces;

int CurrentScreen;

void initialize_display(WindowManager *window){
    CurrentScreen = MAINSCREEN;
    //General stuff
    initialize_screen(window);
    //MAINSCREEN
    initialize_background(window);
    initialize_console(window);
    initialize_SurfaceText(window);
    initialize_menuItems(window);
}

void initialize_screen(WindowManager *window){

    //Graphics card does rendering
    Screen.renderer = SDL_CreateRenderer(window->sdlWindow, 
                                             -1,
                                             SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 

    //Show 
    SDL_RenderPresent(Screen.renderer);

    int width = window->getWidth() * 0.75;
    int height = window->getHeight() * 0.75;

    //Draw Text
    SDL_CreateTexture(Screen.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,width,height);

}

void initialize_background(WindowManager *window){
   SDL_Surface *surface = IMG_Load("img/1.png");

   //Need to Fix this eventually... low priority
   if(surface == NULL){
      surface = SDL_CreateRGBSurface(0,10,10,10,10,10,10,10);
      SDL_FillRect(surface,TempRectBackground,0);
   }

   if(!(Background = SDL_CreateTextureFromSurface(Screen.renderer,surface))){
      cout << "Failed to make background" << endl;
   }
   //Darken
   SDL_SetTextureColorMod(Background,170,170,170);
   //Set Transparency
   SDL_SetRenderDrawBlendMode(Screen.renderer,SDL_BLENDMODE_BLEND);
   
}

void initialize_console(WindowManager *window){
   int width = window->getWidth();
   int height = window->getHeight();

   int console_width =  (int)(0.90 * width);
   int console_height = (int)(0.90 * height);

   // calculate the position of the top-left corner of the rectangle
   int console_x = (int)((width - console_width) / 2);
   int console_y = (int)((height - console_height) / 2);

   // set console location
   Console.consoleRect.x = console_x;    Console.consoleRect.y = console_y;
   Console.consoleRect.w = console_width; Console.consoleRect.h = console_height;
}

void initialize_menuItems(WindowManager *window){
   string max = std::to_string(parse_getCurrentPage()) +  " / " + std::to_string(parse_getPages());
   SDL_Surface *surface = TTF_RenderText_Blended(window->getTextSettings().font,max.c_str(),(SDL_Color){255,255,255});
//   SDL_Surface *surface = TTF_RenderText_Solid(window->getTextSettings().font,max.c_str(),(SDL_Color){255,255,255});
   MainElements.currentPage = SDL_CreateTextureFromSurface(Screen.renderer,surface);
}

void initialize_SurfaceText(WindowManager *window){

    text Text = window->getTextSettings();

    for(int i = 0;i<parse_getNumLines();i++){
       string line = parse_getText().at(i);
       SDL_Surface *currentSurface = TTF_RenderUTF8_Blended(Text.font,line.c_str(),(SDL_Color){0,0,0}); //wraps text around
//       SDL_Surface *currentSurface = TTF_RenderText_Blended(Text.font,line.c_str(),(SDL_Color){0,0,0}); //wraps text around
//       SDL_Surface *currentSurface = TTF_RenderText_Solid(Text.font,line.c_str(),(SDL_Color){0,0,0});
       TextSurfaces.push_back(currentSurface);
    }
}

/*  Helper function for rendering certain Backgrounds
    TODO Expland role to accept int and render according to what background
  */
void display_RenderBackground(){
    //Only render background, no need to present since other stuff will always need to be rendered on top of it
    SDL_RenderCopy(Screen.renderer,display_getBackground(),NULL,NULL);
}

void display_RenderMenuItems(WindowManager *window){
//   SDL_DestroyTexture(Screen.text);
   SDL_Rect displayText;

   displayText.x = Console.consoleRect.w;
   displayText.y = Console.consoleRect.h;
   displayText.w = Console.consoleRect.w/9;
   displayText.h = Console.consoleRect.h/9;
   SDL_RenderCopy(Screen.renderer,MainElements.currentPage,NULL,&displayText);
}

void display_RenderConsole(WindowManager *window){
    text textSettings = window->getTextSettings();
    SDL_SetRenderDrawColor(Screen.renderer,  textSettings.backgroundColor.r, 

                                             textSettings.backgroundColor.g, 
                                             textSettings.backgroundColor.b, 
                                             textSettings.backgroundColor.a); //Background color of Console

    SDL_SetRenderDrawBlendMode(Screen.renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(Screen.renderer, &Console.consoleRect); 


    SDL_RenderCopy(Screen.renderer,Screen.text,NULL,&Console.consoleRect);

}


/* Render text starting at certain index returns index it stopped at */
void display_MainScreen_RenderText(WindowManager *window){

    SDL_DestroyTexture(Screen.text);

    int offset = 0;

    //offsetting is necessary
   //Page 1 means first display lines ex 10 starting at index 0
    int page = parse_getCurrentPage();
    page--; 

    int currentIndex = page * window->getDisplayLines();

    if(currentIndex > parse_getNumLines()){
       currentIndex = parse_getNumLines() % window->getDisplayLines();
       currentIndex = parse_getNumLines() - currentIndex;
    }

    //Display Text
    SDL_Rect displayText;

    int xAlign = Console.consoleRect.x/2;
    int yAlign = Console.consoleRect.y/2;

    for(int i = 0;i<window->getDisplayLines();i++){
       int text_width = TextSurfaces.at(currentIndex)->w;
       int text_height = TextSurfaces.at(currentIndex)->h;

       displayText.x = Console.consoleRect.x + xAlign;
       displayText.y = Console.consoleRect.y + yAlign + offset;
       displayText.w = text_width;
       displayText.h = text_height;

  	    Screen.text = SDL_CreateTextureFromSurface(Screen.renderer, TextSurfaces.at(currentIndex));

//          cout << parse_getText().at(currentIndex) << endl;
      SDL_RenderCopy(Screen.renderer,Screen.text,NULL,&displayText);

       offset+= window->getTextOffset();
       currentIndex++;

       if(currentIndex >= parse_getNumLines()){
         break;
       }

    }

}

void display_MainScreen(WindowManager *window){
    SDL_RenderClear(Screen.renderer);
    SDL_DestroyTexture(Screen.text);
    display_RenderBackground();
    display_RenderMenuItems(window);
    display_RenderConsole(window);
    display_MainScreen_RenderText(window);
    SDL_RenderPresent(Screen.renderer);
}

/*
   Renders background, console, and advances text
*/
void display_MainScreen_ScrollTextForward(WindowManager *window){
    parse_incrementPage();
    string max = std::to_string(parse_getCurrentPage()) +  " / " + std::to_string(parse_getPages());
    SDL_Surface *surface = TTF_RenderText_Blended(window->getTextSettings().font,max.c_str(),(SDL_Color){255,255,255});
    MainElements.currentPage = SDL_CreateTextureFromSurface(Screen.renderer,surface);

    SDL_RenderClear(Screen.renderer);
    SDL_DestroyTexture(Screen.text);
    display_RenderBackground();
    display_RenderMenuItems(window);
    display_RenderConsole(window);
    display_MainScreen_RenderText(window);
    SDL_RenderPresent(Screen.renderer);

}

void display_MainScreen_ScrollTextBackward(WindowManager *window){
    parse_decrementPage();
    string max = std::to_string(parse_getCurrentPage()) +  " / " + std::to_string(parse_getPages());
    SDL_Surface *surface = TTF_RenderText_Blended(window->getTextSettings().font,max.c_str(),(SDL_Color){255,255,255});
    MainElements.currentPage = SDL_CreateTextureFromSurface(Screen.renderer,surface);
    
    SDL_RenderClear(Screen.renderer);
    SDL_DestroyTexture(Screen.text);
    display_RenderBackground();
    display_RenderMenuItems(window);
    display_RenderConsole(window);

    display_MainScreen_RenderText(window);
    SDL_RenderPresent(Screen.renderer);

    
}

screen display_getScreen(){
   return Screen;
}

console display_getConsole(){
   return Console;
}

SDL_Texture *display_getBackground(){
   return Background;
}

vector<SDL_Surface*> display_getSurfaceText(){
    return TextSurfaces;
}

int display_getCurrentScreenIndex(){
   return CurrentScreen;
}


void display_shutdown(WindowManager *window){
   //Font
   TTF_Quit();

   //Screen
   SDL_DestroyRenderer(Screen.renderer);

   //Console
   SDL_FreeSurface(Console.surfaceConsole);
   SDL_DestroyTexture(Console.textureMessage);

   //MainScreen Menu
   SDL_DestroyTexture(MainElements.currentPage);

   //Text
   for(int i = 0;i<parse_getNumLines();i++){
        SDL_FreeSurface(TextSurfaces.at(i));
   }

   SDL_Quit();
}