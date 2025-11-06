#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "double_string.hpp"


using std::string;


struct LineTokens { string a, b; bool ok; };


static LineTokens readTwoTokens(const string& line) {
std::istringstream iss(line);
string a, b;
if (!(iss >> a >> b)) return {"","",false};
// Ignore extra tokens after the second (spec says two per line).
return {a,b,true};
}


int main(int argc, char** argv) {
std::ios::sync_with_stdio(false);


string path;
if (argc >= 2) {
path = argv[1];
} else {
std::cout << "Enter path to test file: ";
std::getline(std::cin, path);
}


std::ifstream fin(path);
if (!fin) {
std::cerr << "ERROR: cannot open file '" << path << "'\n";
return 1;
}


string line;
size_t lineNo = 0;
while (std::getline(fin, line)) {
++lineNo;
if (line.empty()) continue; // skip blank lines
auto tok = readTwoTokens(line);
if (!tok.ok) {
std::cout << "LINE " << lineNo << ": INVALID: missing tokens\n";
continue;
}
bool v1 = isValidDouble(tok.a);
bool v2 = isValidDouble(tok.b);
if (!v1 || !v2) {
std::cout << "LINE " << lineNo << ": ";
if (!v1) std::cout << "INVALID: " << tok.a << ' ';
if (!v2) std::cout << "INVALID: " << tok.b;
std::cout << "\n";
continue;
}
DecNum A = parseDec(tok.a);
DecNum B = parseDec(tok.b);
DecNum C = add(A, B);
std::cout << "LINE " << lineNo << ": SUM: "
<< toString(A) << " + " << toString(B) << " = " << toString(C) << "\n";
}


return 0;
}
