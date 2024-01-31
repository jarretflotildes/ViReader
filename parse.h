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
//string lineLongerCase(string line,int i);

string getLastWord(string line);

int parse_getNumLines();
vector<string> *parse_getTxt();
bool containSpace(string line);
string parse_getPrevious();

void print_file();

#endif