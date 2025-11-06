#pragma once
#include <string>
#include <utility>


// Represents a validated, normalized decimal string number.
// Invariants after normalize():
// - intPart: non-empty, no leading zeros unless the value is zero ("0")
// - fracPart: may be empty; if non-empty, no trailing zeros
// - sign: '+' or '-'; for zero value, sign is '+'
struct DecNum {
char sign = '+'; // '+' or '-'
std::string intPart; // digits only, no leading zeros except "0"
std::string fracPart; // digits only, may be empty
};


// Returns true if s is a valid double-format string per the lab spec.
bool isValidDouble(const std::string& s);


// Parses a valid string into DecNum (no conversion to built-in numeric types).
// Precondition: isValidDouble(s) == true
DecNum parseDec(const std::string& s);


// Normalizes a DecNum in-place (trim zeros, fix -0, etc.).
void normalize(DecNum& x);


// Compares magnitudes |a| and |b|. Returns -1, 0, +1.
int cmpMagnitude(const DecNum& a, const DecNum& b);


// Returns canonical string form from DecNum (observing normalization rules).
std::string toString(const DecNum& x);


// x + y with proper sign handling, done in string arithmetic.
DecNum add(const DecNum& x, const DecNum& y);


// Computes |a| + |b| on magnitudes only (signless), returns positive DecNum.
DecNum addMagnitude(const DecNum& a, const DecNum& b);


// Computes |a| - |b| assuming |a| >= |b|, returns non-negative DecNum.
DecNum subMagnitudeAssumingAGeqB(const DecNum& a, const DecNum& b);
