#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "parse.h"
#include "display.h"
#include "engine.h"
#include "controls.h"

#include <chrono> //XXX REMOVE IN WORKING VERSIONS

#include <string>

#include <SDL2/SDL.h>

int main(int args, char *argv[]){
 using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();
        initialize_parse(argv[1]);
for(int i = 0;i<parse_getNumLines();i++){
string line = parse_CutLine(i);
std::cout << line << std::endl;
}
//    initialize_display();
//    initialize_controls();

//    engine_driver();

//    controls_shutdown();
//    display_shutdown();
//    parse_shutdown(); 
auto t2 = high_resolution_clock::now();

    /* Getting number of milliseconds as an integer. */
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

    std::cout << std::endl << "IT TOOK " << ms_int.count() << "M/S TO COMPLETE\n";
    


    return EXIT_SUCCESS;

}