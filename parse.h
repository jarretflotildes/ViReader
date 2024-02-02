#ifndef PARSE_H
#define PARSE_H

#include <vector>
#include <string>

using std::string;
using std::vector;

void initialize_parse(char *fName);
void extract_text(char *fName);
void parse_shutdown();

string parse_CutLine(int i);
string cutLine_Case1(string firstHalf, string secondHalf, string firstHalf_lastWord ,int i);
string cutLine_Case2(string firstHalf, string secondHalf, string firstHalf_lastWord ,int i);

string getLastWord(string line);

int parse_getNumLines();
vector<string> parse_getText();
bool containSpace(string line);

void print_file();

#endif