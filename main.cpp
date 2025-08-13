#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "parse.h"
#include "display.h"
#include "engine.h"
#include "window.h"
#include "test.h"

#include <chrono> //For testing speeds of algorithms

#include <string>

#include <SDL2/SDL.h>

using std::cout;
using std::endl;

//One line to change between prod and testing
#define TESTING 1

void driver(char *argv[]){
    WindowManager window = WindowManager(0);
    initialize_parse(argv[1],window.getTextLimit(),window.getDisplayLines());
    initialize_display(&window);
    engine_driver(&window); 
    window.shutdown_Window();
    display_shutdown(&window);
}

void test(char *argv[]){
//    test_basic_sdl();
    test_parse(argv);
    //test_display_init();
    //test_display_scrollForward(argv);
    //test_window();
}

int main(int args, char *argv[]){
    if(args != 2){
        cout << "Need one file!" << endl;
        return -1;
    }
    cout << "STARTING PROGRAM..." << endl;

    if(TESTING){
        test(argv);
    } else {
        driver(argv);
    }
    cout << "SHUTTING DOWN..." << endl;
    return EXIT_SUCCESS;

}