#ifndef PARSE_H
#define PARSE_H

#include <vector>
#include <string>

using std::string;
using std::vector;

void initialize_parse(char *fName,int characterLimit,int displayLimit);
void extract_text(char *fName);
void format_text();

string parse_CutLine(int i);
string cutLine_Case1(string line, string firstHalf, string secondHalf, string firstHalf_lastWord,int i);
string cutLine_Case2(string line, string firstHalf, string secondHalf, string firstHalf_lastWord ,int i);

string getFirstWord(string line);
string getLastWord(string line);
size_t getLastWordBoundary(const string &str, size_t max_chars);
//UTF Helpers
size_t utf8_length(const string &str);
string utf8_substr(const string& str, size_t start, size_t length = string::npos);


int parse_getNumLines();
int parse_getPages();
int parse_getCurrentPage();
void parse_incrementPage();
void parse_decrementPage();



vector<string> parse_getText();
bool containSpace(string line);

void print_file();

#endif