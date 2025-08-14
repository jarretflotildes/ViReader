#include <stdio.h>
#include <stdlib.h>

#include <string>

#include <iostream>
#include <vector>

#include <bits/stdc++.h>
#include <locale>
#include <codecvt>
 
#include "parse.h"
#include "display.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

int NUM_LINES;
int CharacterLimit;  // Now represents visual character count, not byte count
int DisplayLimit;
int Pages;
int CurrentPage;

vector<string> TXT_FILE;

/**
 * @brief initialize vector TXT_FILE to fName
 * 
 * @param fname name of file to open
 * @param characterLimit number of visual characters allowed specified by window.textCharacterLimit
 * @param displayLimit number of lines showed on each page specified by window.displayLines 
 */
void initialize_parse(char *fName, int characterLimit, int displayLimit) {
    NUM_LINES = 0;
    CharacterLimit = characterLimit;
    DisplayLimit = displayLimit;

    extract_text(fName);

    // FORMAT TEXT
    for (int i = 0; i < parse_getNumLines(); i++) {
        parse_CutLine(i);
//cout << TXT_FILE.at(i) << endl;
    }

    format_text();

//   double tempPages = ((double)NUM_LINES/DisplayLimit) + 1;
   double tempPages = ((double)NUM_LINES / DisplayLimit);

    if (DisplayLimit > NUM_LINES) {
        Pages = 1;
    } else if (tempPages == 0) {
        Pages = 1;
    } else {
        Pages = ceil(tempPages);
    }

   /* May need to update later so can load up previously loaded file XXX*/
   CurrentPage = 1;

/*
cout << "There are " << NUM_LINES << " Lines." << endl;
cout << "There are " << Pages << " Pages." << endl;
*/
   cout << "Parse Initialized Successfully..." << endl;
}

/**
 * @brief Extract text from file and input contents into vector TXT_FILE
 * 
 * @param fName - name of file
 */
void extract_text(char *fName) {
    std::ifstream file(fName);
    string line = "";

    // Set locale to handle UTF-8
    file.imbue(std::locale("en_US.UTF-8"));

    if (file.is_open()) {
        int i = 0;
        while (getline(file, line)) {
            TXT_FILE.push_back(line);
//cout << line << endl;
            i++;
        }

        NUM_LINES = i;                                 //Assign Global Num_lines

        // Empty file
        if (NUM_LINES == 0) {
            TXT_FILE.push_back(" ");
            NUM_LINES = 1;
        }
    } else {
        printf("parse: error loading text file\n");
        exit(-1);
    }

    file.close();
}

/*
   Read Text and format into proper format
   Remove all special characters from TXT_FILE
*/
void format_text() {  
   // Remove trailing \r and \n characters
    for (auto& line : TXT_FILE) {
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
    }
}

/** 
   Cut current string from table into proper format to display on screen
   Limit current string to up to character limit (counting visual characters, not bytes)
      3 cases 
      1) Last word in first half < character limit
      2) Last word in first half >= character limit 
      3) String is already fine
   @param i - line of vector
**/
string parse_CutLine(int i) {
    string line = TXT_FILE.at(i);
    int characterLimit = CharacterLimit;
    if(containsCJKChars(line)){
        characterLimit *= 0.49;
    }
    
    char *buffer = (char*)line.c_str();
    buffer[strcspn(line.c_str(), "\r\n")] = 0;
    line.assign(buffer);

    if ((int)utf8_length(line) > characterLimit) {
        size_t split_pos = getLastWordBoundary(line, characterLimit);
        string firstHalf = utf8_substr(line, 0, split_pos);
        string secondHalf = utf8_substr(line, split_pos);
        string firstHalf_lastWord = getLastWord(firstHalf);

        //LAST WORD IS SAME AS FIRST HALF, IE ONLY WORD IN LINE OR WAS CUT OFF
        //REMOVE FROM CONSIDERATION
        if(firstHalf == firstHalf_lastWord){
           firstHalf_lastWord = "";
        }

        // Remove trailing space from first half
        while (!firstHalf.empty() && firstHalf.back() == ' ') {
            firstHalf.pop_back();
        }
        
        // Remove leading space from second half
        while (!secondHalf.empty() && secondHalf.front() == ' ') {
            secondHalf.erase(0, 1);
        }

        if (!secondHalf.empty()) {
            //remove any special characters at end of string
            if(secondHalf.back() == '\n'){ 
               //cout << "removing " << int(secondHalf.at(secondHalf.length()-1)) << endl;;
               secondHalf.erase(secondHalf.length()-1);
            }

            if (i + 1 < NUM_LINES) {
                string next = TXT_FILE.at(i + 1);
                char nextCharacter = next.at(0);
                //Append to next line ONLY when next line is not new paragraph/dialogue/whatever
                if (nextCharacter != '\r' && //enter
                    nextCharacter != '\n' && //new line 
                    nextCharacter != '\v') { //vertical tab
                    string newLine = secondHalf + " " + next;
                    TXT_FILE.at(i + 1) = newLine;
                } else {
                    TXT_FILE.insert(TXT_FILE.begin() + i + 1, secondHalf);
                    NUM_LINES = TXT_FILE.size();   //Update GLOBAL SIZE
                }
            } else {
                TXT_FILE.push_back(secondHalf);
                NUM_LINES = TXT_FILE.size();         //UPDATE GLOBAL SIZE
            }
        }

        TXT_FILE.at(i) = firstHalf; //UPDATE GLOBAL TEXT TABLE
        line = firstHalf;
    }

    return line;
}

// UTF-8 helper functions
size_t utf8_length(const string &str) {
    size_t length = 0;
    for (size_t i = 0; i < str.size(); ) {
        unsigned char c = str[i];
        if (c < 0x80) {
            i += 1;  // ASCII character
        } else if ((c & 0xE0) == 0xC0) {
            i += 2;  // 2-byte character
        } else if ((c & 0xF0) == 0xE0) {
            i += 3;  // 3-byte character
        } else if ((c & 0xF8) == 0xF0) {
            i += 4;  // 4-byte character
        } else {
            i += 1;  // Invalid UTF-8, treat as single byte
        }
        length++;
    }
    return length;
}

// Get UTF-8 substring by character count
string utf8_substr(const string& str, size_t start, size_t length) {
    if (start == 0 && length == string::npos) {
        return str;
    }
    
    size_t byte_start = 0;
    size_t char_count = 0;
    
    // Find byte position for start character
    for (size_t i = 0; i < str.size() && char_count < start; ) {
        unsigned char c = str[i];
        if (c < 0x80) {
            i += 1;
        } else if ((c & 0xE0) == 0xC0) {
            i += 2;
        } else if ((c & 0xF0) == 0xE0) {
            i += 3;
        } else if ((c & 0xF8) == 0xF0) {
            i += 4;
        } else {
            i += 1;
        }
        char_count++;
        if (char_count == start) {
            byte_start = i;
            break;
        }
    }
    
    if (length == string::npos) {
        return str.substr(byte_start);
    }
    
    // Find byte length for the desired character length
    size_t byte_length = 0;
    char_count = 0;
    
    for (size_t i = byte_start; i < str.size() && char_count < length; ) {
        unsigned char c = str[i];
        size_t char_bytes = 1;
        
        if (c < 0x80) {
            char_bytes = 1;
        } else if ((c & 0xE0) == 0xC0) {
            char_bytes = 2;
        } else if ((c & 0xF0) == 0xE0) {
            char_bytes = 3;
        } else if ((c & 0xF8) == 0xF0) {
            char_bytes = 4;
        }
        
        i += char_bytes;
        byte_length += char_bytes;
        char_count++;
    }
    
    return str.substr(byte_start, byte_length);
}

// Find last complete word boundary before character limit
size_t getLastWordBoundary(const string &str, size_t characterLimit) {
    if (utf8_length(str) <= characterLimit) {
        return utf8_length(str);
    }
    
    // Find the character position for max_chars
    size_t char_count = 0;
    size_t last_space_char = 0;
    bool found_space = false;
    
    for (size_t i = 0; i < str.size() && char_count < characterLimit; ) {
        unsigned char c = str[i];
        
        if (c == ' ') {
            last_space_char = char_count;
            found_space = true;
        }
        
        // Move to next character
        if (c < 0x80) {
            i += 1;
        } else if ((c & 0xE0) == 0xC0) {
            i += 2;
        } else if ((c & 0xF0) == 0xE0) {
            i += 3;
        } else if ((c & 0xF8) == 0xF0) {
            i += 4;
        } else {
            i += 1;
        }
        char_count++;
    }
    return found_space ? last_space_char + 1 :characterLimit;
}


// Check if string contains CJK characters
bool containsCJKChars(const string &str) {
    for (size_t i = 0; i < str.size(); ) {
        unsigned char c = str[i];
        
        if (c < 0x80) {
            // ASCII character
            i += 1;
        } else if ((c & 0xE0) == 0xC0) {
            // 2-byte character - skip for now
            i += 2;
        } else if ((c & 0xF0) == 0xE0) {
            // 3-byte character - this is where most CJK characters are
            unsigned char c1 = (i + 1 < str.size()) ? str[i + 1] : 0;
            //unsigned char c2 = (i + 2 < str.size()) ? str[i + 2] : 0;
            
            // Check for common Japanese/CJK Unicode ranges
            // Hiragana: U+3040-U+309F
            // Katakana: U+30A0-U+30FF  
            // CJK Unified Ideographs: U+4E00-U+9FFF
            // CJK Symbols: U+3000-U+303F
            if ((c == 0xE3 && c1 >= 0x80 && c1 <= 0xBF) ||  // U+3000-U+3FFF range
                (c >= 0xE4 && c <= 0xE9) ||                   // U+4000-U+9FFF range
                (c == 0xEF && c1 == 0xBC) ||                  // Full-width characters
                (c == 0xEF && c1 == 0xBD)) {                  // More full-width characters
                return true;
            }
            i += 3;
        } else if ((c & 0xF8) == 0xF0) {
            // 4-byte character
            i += 4;
        } else {
            // Invalid UTF-8, treat as single byte
            i += 1;
        }
    }
    return false;
}



/*
   Get first word in string
*/
string getFirstWord(string line) {
    size_t space_pos = line.find(" ");
    
    if (space_pos != std::string::npos) {
        line = line.substr(0, space_pos + 1);
    }

    return line;
}

//get last word in a string
string getLastWord(string line) {
    std::stringstream ss(line);
    string word;
    string last = line;
  
    while (getline(ss, word, ' ')) {
        if (!word.empty()) {
            last = word;
        }
    }

    return last;   
}

int parse_getNumLines() {
    return NUM_LINES;
}

int parse_getPages() {
    return Pages;
}

int parse_getCurrentPage() {
    return CurrentPage;
}

void parse_incrementPage() {
    CurrentPage++;
    if (CurrentPage > Pages) {
        CurrentPage = 1;
    }
}

void parse_decrementPage() {
    CurrentPage--;
    if (CurrentPage <= 0) {
        CurrentPage = Pages;
    }
}

vector<string> parse_getText() {
    return TXT_FILE;
}

void print_file() {
    for (int i = 0; i < NUM_LINES; i++) {
        cout << "String [" << i << "] = " << TXT_FILE.at(i) << " (Length: " << utf8_length(TXT_FILE.at(i)) << " chars)" << endl;
    }
}