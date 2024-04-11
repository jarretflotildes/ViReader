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

using std::cout;
using std::endl;

void driver(char *argv[]){
    WindowManager window = WindowManager(0);
    initialize_parse(argv[1],window.getTextLimit(),window.getDisplayLines());
    initialize_display(&window);
    engine_driver(&window); 
    window.shutdown_Window();
    display_shutdown(&window);
}

int main(int args, char *argv[]){
cout << "STARTING PROGRAM..." << endl;
    /*
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();
*/
driver(argv);
/*
    auto t2 = high_resolution_clock::now();

    // Getting number of milliseconds as an integer.
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    // Getting number of milliseconds as a double. 
    duration<double, std::milli> ms_double = t2 - t1;

    std::cout << std::endl << "IT TOOK " << ms_int.count() << "M/S TO COMPLETE\n";
*/
cout << "SHUTTING DOWN..." << endl;
    return EXIT_SUCCESS;

}