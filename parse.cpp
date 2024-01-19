#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"

void extract_text(char *fname, char **text, int *rows, int *cols){
   FILE *fptr;
   fptr = fopen(fname,"r");

   char buf[BUFSIZ];

   *rows = 0;
   *cols = 0;

   if(fptr == NULL){
      printf("Invalid data!\n");
      exit(-1);
   } 

   while(fgets(buf,sizeof(BUFSIZ),fptr)){
      *cols = strlen(buf);
      char *array = (char *)malloc((*cols)*sizeof(int));
      strcpy(array,buf);
      text[*rows] = array;
      *rows = *rows + 1;
   }
  
   fclose(fptr);

}

void closeText(char **text,int *rows){
   for(int i = 0;i<*rows;i++){
      //printf("%s",text[i]);
      free(text[i]);
   }

}