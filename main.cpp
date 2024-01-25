#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "parse.h"
#include "display.h"
#include "engine.h"
#include "controls.h"

#include <string>

#include <SDL2/SDL.h>

int main(int args, char *argv[]){

    initialize_parse(argv[1]);
for(int i = 0;i<3;i++){
string line = parse_CutLine(i);
std::cout << line << std::endl;
}
//    initialize_display();
//    initialize_controls();

//    engine_driver();

//    controls_shutdown();
//    display_shutdown();
//    parse_shutdown();

    return EXIT_SUCCESS;

}