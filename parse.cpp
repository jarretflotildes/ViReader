#include <stdio.h>
#include <stdlib.h>

#include <string>

#include <iostream>
#include <vector>

#include <bits/stdc++.h>
 
#include "parse.h"
#include "display.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

int NUM_LINES;
int CharacterLimit;
int DisplayLimit;
int Pages;
int CurrentPage;

vector<string> TXT_FILE;

void initialize_parse(char *fName,int characterLimit,int displayLimit){
    NUM_LINES = 0;
    CharacterLimit = characterLimit;
    DisplayLimit = displayLimit;

    extract_text(fName);

    //FORMAT TEXT
    for(int i = 0;i<parse_getNumLines();i++){
         parse_CutLine(i);
//cout << TXT_FILE.at(i) << endl;
    }

   double tempPages = ((double)NUM_LINES/DisplayLimit) + 1;

   if(DisplayLimit > NUM_LINES){
      Pages = 1;
   } else {
      Pages = ceil(tempPages);
   }

   /* May need to update later so can load up previously loaded file XXX*/
   CurrentPage = 1;



    //format_text(); //TODO: maybe don't need
/*
cout << "There are " << NUM_LINES << " Lines." << endl;
cout << "There are " << Pages << " Pages." << endl;
*/

}

void extract_text(char *fName){
   std::ifstream file(fName);
   string line = "";

   if(file.is_open()){
      int i = 0;
      while (getline(file, line)) {
         TXT_FILE.push_back(line);
//cout << line << endl;
         i++;
      }
        NUM_LINES = i;                                 //Assign Global Num_lines
   } else {
      printf("error loading text file\n");
      exit(-1);
   }

   file.close();
}
/*
   Read Text and format into proper format
      Remove all special characters
*/
void formatText(){
//Implement this XXX
}

/*
   Cut current string from table into proper format to display on screen
   Limit current string to up to character limit
      3 cases 
      1) Last word in first half < character limit
      2) Last word in first half >= character limit 
      3) String is already fine
*/
string parse_CutLine(int i){

   string line = TXT_FILE.at(i);
   int characterLimit = CharacterLimit;

   char *buffer = (char*)line.c_str();
   buffer[strcspn(line.c_str(), "\r\n")] = 0;
   line.assign(buffer);

   if((int)line.length() > characterLimit){
      string firstHalf = line.substr(0,characterLimit);
      string secondHalf = line.substr(characterLimit,line.length());

      string firstHalf_lastWord = getLastWord(firstHalf);

      //LAST WORD IS SAME AS FIRST HALF, IE ONLY WORD IN LINE OR WAS CUT OFF
      //REMOVE FROM CONSIDERATION
      if(firstHalf == firstHalf_lastWord){
         firstHalf_lastWord = "";
      }
      
      if(firstHalf_lastWord.empty() == false){
//      if((int)firstHalf_lastWord.length() < CHARACTER_LIMIT){
         line = cutLine_Case1(line,firstHalf,secondHalf,firstHalf_lastWord,i);
      } else {
         line = cutLine_Case2(line,firstHalf,secondHalf,firstHalf_lastWord,i);
      }
   }

   return line;
}

/*
   Last word in first half < character limit
      - does nothing if secondhalf is empty
      - Removes any leftover letters from first half 
      - Returns formatted firsthalf while updating/adding next value in table
*/
string cutLine_Case1(string line, string firstHalf, string secondHalf, string firstHalf_lastWord,int i){
   //No need to do anything else if second half is empty
   if(secondHalf.empty() == true){
      return firstHalf;
   } 

   if(firstHalf_lastWord != ""){
      //remove leftovers of last word
      if(firstHalf.back() == ' '){

      }

      while(firstHalf.back() != ' '){
         firstHalf.pop_back();
      }
   } 

   string secondHalf_firstWord = getFirstWord(secondHalf);

   /*
cout << "First Half    1: " << firstHalf << endl;
cout << "Second Half   2: " << secondHalf << endl;
cout << "LAST WORD IS  3: " << firstHalf_lastWord << endl; 
cout << "FIRST WORD IS 4: " << secondHalf_firstWord << endl;
cout << "COMBINE       5: " << firstHalf << firstHalf_lastWord << secondHalf << endl;
cout << "Original       : " << line << endl;
*/
   //perfect match if reconstructed original does not equal so turn last word to empty string
   if(line != (firstHalf + firstHalf_lastWord + secondHalf)){
        firstHalf_lastWord = "";
   }
/*
   char *buffer = (char*)secondHalf.c_str();
   buffer[strcspn(secondHalf.c_str(), "\r\n")] = 0; //remove CR, CL, etc
   secondHalf.assign(buffer);
*/

   //remove any special characters at end of string
   if(secondHalf.back() == '\n'){ 
      //cout << "removing " << int(secondHalf.at(secondHalf.length()-1)) << endl;;
      secondHalf.erase(secondHalf.length()-1);
   }

   if(i+1 < NUM_LINES){
      string next = TXT_FILE.at(i+1);
      char nextCharacter = next.at(0);
 
      //Append to next line ONLY when next line is not new paragraph/dialogue/whatever
      if(nextCharacter != '\r' && //enter
         nextCharacter != '\n' && //new line 
         nextCharacter != '\v') { //vertical tab
            string newLine = firstHalf_lastWord + secondHalf + " " + TXT_FILE.at(i+1);
            TXT_FILE.at(i+1) = newLine;

         } else{
            string newLine = firstHalf_lastWord + secondHalf;
            TXT_FILE.insert(TXT_FILE.begin()+i+1,newLine);
            NUM_LINES = TXT_FILE.size();   //Update GLOBAL SIZE 
      }
   } else {
      string newLine = firstHalf_lastWord + secondHalf;
      TXT_FILE.push_back(newLine);
      NUM_LINES = TXT_FILE.size();         //UPDATE GLOBAL SIZE
   }

   TXT_FILE.at(i) = firstHalf; //UPDATE GLOBAL TEXT TABLE

   return firstHalf;
}

/*
  Extremely Rare Case, for now just leave leftover text and  
*/
string cutLine_Case2(string line, string firstHalf, string secondHalf, string firstHalf_lastWord,int i){
   //remove any special characters at end of string
   if(secondHalf.back() == '\n' || secondHalf.back() == '\r'){ 
      //cout << "removing " << int(secondHalf.at(secondHalf.length()-1)) << endl;;
      secondHalf.erase(secondHalf.length()-1);
   }

   //perfect match if reconstructed original does not equal so turn last word to empty string
   if(line != (firstHalf + firstHalf_lastWord + secondHalf)){
        firstHalf_lastWord = "";
   }

   char lastCharacter = firstHalf.at(firstHalf.length()-1);
   firstHalf.at(firstHalf.length()-1) = '-';

   if(i+1 < NUM_LINES){
      string next = TXT_FILE.at(i+1);
      char nextCharacter = next.at(0);

      //Append to next line ONLY when next line is not new paragraph/dialogue/whatever
      if(nextCharacter != '\r' && //enter
         nextCharacter != '\n' && //new line 
         nextCharacter != '\v') { //vertical tab
            string newLine = lastCharacter + secondHalf + " " + TXT_FILE.at(i+1);
            TXT_FILE.at(i+1) = newLine;
         } else{
            string newLine = lastCharacter + secondHalf;
            TXT_FILE.insert(TXT_FILE.begin()+i+1,newLine);
            NUM_LINES = TXT_FILE.size(); //UPDATE GLOBAL SIZE
      }
   } else {
      string newLine = lastCharacter + firstHalf_lastWord + secondHalf;
      TXT_FILE.push_back(newLine);
      NUM_LINES = TXT_FILE.size();         //UPDATE GLOBAL SIZE
   }

   TXT_FILE.at(i) = firstHalf; //UPDATE GLOBAL TEXT TABLE
   return firstHalf;

}

/*
   Get first word in string
*/
string getFirstWord(string line){
   
   size_t space_pos = line.find(" ");
   
   if (space_pos != std::string::npos) {
      line = line.substr(0,space_pos + 1);
   }

   return line;

}

//get last word in a string
string getLastWord(string line){

   std::stringstream ss(line);

   string last = line;
  
   while(getline(ss, line, ' ' )) {
      last = line;
   }

   return last;   
}

int parse_getNumLines(){
   return NUM_LINES;
}

int parse_getPages(){
   return Pages;
}

int parse_getCurrentPage(){
   return CurrentPage;
}

void parse_incrementPage(){
   CurrentPage++;
   if(CurrentPage > Pages){
      CurrentPage = 1;
   }

}

void parse_decrementPage(){
   CurrentPage--;
   if(CurrentPage <= 0){
      CurrentPage = Pages;
   }
}

vector<string> parse_getText(){
   return TXT_FILE;
}

void print_file(){
    for (int i = 0; i < NUM_LINES; i++) {
      cout << "String [" << i << "] = " << TXT_FILE.at(i) << endl;
      //std::cout << TXT_FILE.at(i) << std::endl;
    }
}