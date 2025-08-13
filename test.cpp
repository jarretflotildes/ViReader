#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "parse.h"
#include "display.h"
#include "engine.h"
#include "window.h"

#include <chrono> //For testing speeds of algorithms
#include <string>
#include <SDL2/SDL.h>

/**
 * @brief 
 * 
 * @return int 
 */
int test_basic_sdl(){
    printf("Initializing SDL...\n");

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    printf("SDL initialized, quitting immediately...\n");
    // Quit SDL
    SDL_Quit();
    return 0;
}

/**
 * @brief Test parse
 * 
 * @param argv input file
 */
void test_parse(char *argv[]){
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    auto t1 = high_resolution_clock::now();
    int textCharacterLimit = 50;
    int displayLines = 10;
    initialize_parse(argv[1],textCharacterLimit,displayLines);
    print_file();
    auto t2 = high_resolution_clock::now();
    // Getting number of milliseconds as an integer.
    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    // Getting number of milliseconds as a double. 
    duration<double, std::milli> ms_double = t2 - t1;
    std::cout << std::endl << "IT TOOK " << ms_int.count() << "M/S TO COMPLETE\n";
}

void test_display_init(){
    WindowManager window = WindowManager(0);
    initialize_display(&window);
    display_shutdown(&window);
    window.shutdown_Window();
}

void test_display_scrollForward(char *argv[]){
    WindowManager window = WindowManager(0);
    initialize_display(&window);
    initialize_parse(argv[1],window.getTextLimit(),window.getDisplayLines());
    display_MainScreen_ScrollTextForward(&window);
    display_shutdown(&window);
    window.shutdown_Window();
}

void test_window(){
    WindowManager window = WindowManager(0);
    window.shutdown_Window();
}