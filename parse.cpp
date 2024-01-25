#include <stdio.h>
#include <stdlib.h>

#include <string>

#include <iostream>
#include <fstream>
#include <vector>

#include "parse.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

int Line_limit = 30;

string Previous;
vector<string> TXT_FILE[1];

int Num_Lines;

void initialize_parse(char *fName){
    Num_Lines = 0;
    extract_text(fName);
    Previous = "";
}



void extract_text(char *fName){
   std::ifstream file(fName);
   string line = "";

   if(file.is_open()){

      int i = 0;
      while (getline(file, line)) {
         TXT_FILE->push_back(line);
         i++;
      }
        Num_Lines = i;                                 //Assign Global Num_lines
   } else {
      printf("error loading text file\n");
      exit(-1);
   }

   file.close();
}

/*
    Cut String into proper format
    store excess into previous
*/
string parse_CutLine(string line){

   if((int)line.length() >= Line_limit){
      string firstHalf = line.substr(0,Line_limit);
      string secondHalf = line.substr(Line_limit,line.length());

      string firstHalf_lastWord  = getLastWord(firstHalf);

      char firstHalf_lastCharacter   = firstHalf_lastWord.at(firstHalf_lastWord.length()-1);
      char secondHalf_firstCharacter = secondHalf.at(0);

      while(firstHalf.at(firstHalf.length()-1) != ' '){
         firstHalf.pop_back();
      }

      line = firstHalf;

      //cout << line << endl;
      
      //word is split from line limit, move word to next line
      if(firstHalf_lastCharacter != ' ' && 
         secondHalf_firstCharacter != ' '){
            if (!secondHalf.empty() && 
               (secondHalf.back() == '\n' || secondHalf.back() == ' ')) {
               secondHalf.pop_back();
            }
            Previous = firstHalf_lastWord + secondHalf;
            //cout << Previous << endl;
      }

   } else {
      Previous = "";
   }

   return line;

}

string getLastWord(string line){
   int pos = line.size();
   while (line[pos] == ' ' && pos > 0) --pos;
   if (pos == 0) { /* string consists entirely of spaces */ 
      line = " "; 
   } else {
      line = line.substr(line.find_last_of(' ', pos));
   }
   return line;   
}

int parse_getNumLines(){
   return Num_Lines;
}


vector<string> *parse_getTxt(){
   return TXT_FILE;
}

string parse_getPrevious(){
   return Previous;
}

void print_file(){
    for (int i = 0; i < Num_Lines; i++) {
      cout << "String [" << i << "] = " << TXT_FILE->at(i) << endl;
      //std::cout << TXT_FILE->at(i) << std::endl;
    }
}