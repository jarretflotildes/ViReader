#include <stdio.h>
#include <stdlib.h>

#include "parse.h"
#include "display.h"

#include <SDL2/SDL.h>

#define MAXROWS 5000

int main(int args, char *argv[]){
   /* 
    char *fName=argv[1];   
    char *text[MAXROWS];
    int rows = 0;
    int cols = 0;

    printf("Opening file %s...\n",fName);

    extract_text(fName,text,&rows,&cols);
    closeText(text,&rows);

    printf("\nFinished,,, exiting\n");
*/
    initialize_display();
    display_driver();
    display_shutdown();

    return EXIT_SUCCESS;
}