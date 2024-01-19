#ifndef EXTRACT_H
#define EXTRACT_H

void extract_text(char *fname, char **text,int *rows,int *cols);
void closeText(char **text,int *rows);

#endif