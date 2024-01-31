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

int Line_limit = 63;

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
*/
string parse_CutLine(int i){

   string line = TXT_FILE->at(i);

   if((int)line.length() >= Line_limit){
      string firstHalf = line.substr(0,Line_limit);
      string secondHalf = line.substr(Line_limit,line.length());

      string firstHalf_lastWord  = getLastWord(firstHalf);

      //If Last word is less than character limit should move it to next line
      if((int)firstHalf_lastWord.length() < Line_limit){
         line = cutLine_Case1(line,firstHalf,secondHalf,firstHalf_lastWord, i);
      }

/*else {
         //If last word is actually larger than character limit
         //should add hypen (-) end of line than continue it on next line 
         char firstHalf_lastCharacter   = firstHalf_lastWord.at(firstHalf_lastWord.length()-1);
         char secondHalf_firstCharacter = secondHalf.at(0);

    

         line = firstHalf;

         //word is split from line limit, move word to next line
         if(firstHalf_lastCharacter != ' ' && 
            secondHalf_firstCharacter != ' '){
               if (!secondHalf.empty() && 
                  (secondHalf.back() == '\n' || secondHalf.back() == ' ')) {
                  secondHalf.pop_back();
               }
         }

         //      

         //strip /n
         secondHalf.erase(secondHalf.length()-1);

         if(i+1 < Num_Lines){
            string newLine = firstHalf_lastWord + secondHalf + " " + TXT_FILE->at(i+1);
            TXT_FILE->at(i+1) = newLine;
         } else {
            string newLine = firstHalf_lastWord + secondHalf;
            TXT_FILE->push_back(newLine);
            Num_Lines++;
         }


      }*/
   }

   return line;
}

string cutLine_Case1(string line, string firstHalf, string secondHalf, string firstHalf_lastWord,int i){

   char firstHalf_lastCharacter = firstHalf_lastWord.at(firstHalf_lastWord.length()-1);
   
   //No need to do anything else if second half is empty
   if(secondHalf.empty() == true){
      return firstHalf;
   } 

   //remove leftovers of last word
   while(firstHalf.at(firstHalf.length()-1) != ' '){
      firstHalf.pop_back();
   }

   line = firstHalf;

   char secondHalf_firstCharacter = secondHalf.at(0);

   //word is split from line limit, move word to next line
   if(firstHalf_lastCharacter != ' ' && 
   secondHalf_firstCharacter != ' '){
      if (!secondHalf.empty() && 
         (secondHalf.back() == '\n' || secondHalf.back() == ' ')) {
         secondHalf.pop_back();
      }
   }

   //remove any special characters at end of string
   if(secondHalf.at(secondHalf.length()-1) == '\n' || secondHalf.at(secondHalf.length()-1) == '\r'){ 
      //cout << "removing " << int(secondHalf.at(secondHalf.length()-1)) << endl;;
      secondHalf.erase(secondHalf.length()-1);
   }

   if(i+1 < Num_Lines){
      string newLine = firstHalf_lastWord + secondHalf + " " + TXT_FILE->at(i+1);
      TXT_FILE->at(i+1) = newLine;
   } else {
      string newLine = firstHalf_lastWord + secondHalf;
      TXT_FILE->push_back(newLine);
      Num_Lines++;
   }

   return line;
}

//get last word in a string
string getLastWord(string line){
   int pos = line.size();
   while (line[pos] == ' ' && pos > 0) --pos;

   if (pos == 0) { /* string consists entirely of spaces */ 
      line = " "; 
   } else {
      line = line.substr(line.find_last_of(' ', pos));
   }

   if(line.at(0) == ' '){
      line.erase(line.begin());
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