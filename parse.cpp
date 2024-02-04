#include <stdio.h>
#include <stdlib.h>

#include <string>

#include <iostream>
#include <vector>

#include <bits/stdc++.h>
 
#include "parse.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

int CHARACTER_LIMIT;
int NUM_LINES;

vector<string> TXT_FILE;

void initialize_parse(char *fName){
    CHARACTER_LIMIT = 50;
    NUM_LINES = 0;
    extract_text(fName);

    //FORMAT TEXT
    for(int i = 0;i<parse_getNumLines();i++){
         parse_CutLine(i);
cout << "OUTPUT: " << TXT_FILE.at(i) << endl;
    }

}

void parse_shutdown(){

}

void extract_text(char *fName){
   std::ifstream file(fName);
   string line = "";

   if(file.is_open()){
      int i = 0;
      while (getline(file, line)) {
         TXT_FILE.push_back(line);
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
   Cut current string from table into proper format to display on screen
   Limit current string to up to character limit
      3 cases 
      1) Last word in first half < character limit
      2) Last word in first half >= character limit 
      3) String is already fine
*/
string parse_CutLine(int i){

   string line = TXT_FILE.at(i);

   if((int)line.length() > CHARACTER_LIMIT){
      string firstHalf = line.substr(0,CHARACTER_LIMIT);
      string secondHalf = line.substr(CHARACTER_LIMIT,line.length());

      string firstHalf_lastWord = getLastWord(firstHalf);

      //LAST WORD IS SAME AS FIRST HALF, IE ONLY WORD IN LINE OR WAS CUT OFF
      //REMOVE FROM CONSIDERATION
      if(firstHalf == firstHalf_lastWord){
         firstHalf_lastWord = "";
      }
      
      if(firstHalf_lastWord.empty() == false){
//      if((int)firstHalf_lastWord.length() < CHARACTER_LIMIT){
         line = cutLine_Case1(firstHalf,secondHalf,firstHalf_lastWord,i);
      } else {
         line = cutLine_Case2(firstHalf,secondHalf,firstHalf_lastWord,i);
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
string cutLine_Case1(string firstHalf, string secondHalf, string firstHalf_lastWord,int i){
   
   //No need to do anything else if second half is empty
   if(secondHalf.empty() == true){
      return firstHalf;
   } 

   char firstHalf_lastCharacter = firstHalf_lastWord.back();

   if(firstHalf_lastWord != ""){
      //remove leftovers of last word
      while(firstHalf.back() != ' '){
         firstHalf.pop_back();
      }
   } 

   char secondHalf_firstCharacter = secondHalf.at(0);

   //word is split from line limit, move word to next line
   if(firstHalf_lastCharacter != ' ' && 
   secondHalf_firstCharacter != ' '){
      if ((secondHalf.back() == '\n' || secondHalf.back() == ' ') || secondHalf.back() == '\r') {
         secondHalf.pop_back();
      }
   }

   //remove any special characters at end of string
   if(secondHalf.back() == '\n' || secondHalf.back() == '\r'){ 
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
//            cout << int(TXT_FILE->at(i+1).at(0)) << endl;
            string newLine = firstHalf_lastWord + secondHalf + " " + TXT_FILE.at(i+1);
//cout << "RECONSTRUCTED1: " << newLine << endl;
            TXT_FILE.at(i+1) = newLine;

         } else{
            string newLine = firstHalf_lastWord + secondHalf;
//cout << "RECONSTRUCTED2: " << newLine << endl;
            TXT_FILE.insert(TXT_FILE.begin()+i+1,newLine);
            NUM_LINES = TXT_FILE.size();   //Update GLOBAL SIZE 
      }
   } else {
      string newLine = firstHalf_lastWord + secondHalf;
//cout << "RECONSTRUCTED3: " << newLine << endl;
      TXT_FILE.push_back(newLine);
      NUM_LINES = TXT_FILE.size();         //UPDATE GLOBAL SIZE
   }

   TXT_FILE.at(i) = firstHalf; //UPDATE GLOBAL TEXT TABLE

   return firstHalf;
}

/*
  Extremely Rare Case, for now just leave leftover text and  
*/
string cutLine_Case2(string firstHalf, string secondHalf, string firstHalf_lastWord,int i){
   //remove any special characters at end of string
   if(secondHalf.back() == '\n' || secondHalf.back() == '\r'){ 
      //cout << "removing " << int(secondHalf.at(secondHalf.length()-1)) << endl;;
      secondHalf.erase(secondHalf.length()-1);
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
//            cout << int(TXT_FILE->at(i+1).at(0)) << endl;

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
      NUM_LINES = TXT_FILE.size();
      NUM_LINES++;         //UPDATE GLOBAL SIZE
   }

   TXT_FILE.at(i) = firstHalf; //UPDATE GLOBAL TEXT TABLE
   return firstHalf;

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

vector<string> parse_getText(){
   return TXT_FILE;
}

void print_file(){
    for (int i = 0; i < NUM_LINES; i++) {
      cout << "String [" << i << "] = " << TXT_FILE.at(i) << endl;
      //std::cout << TXT_FILE.at(i) << std::endl;
    }
}