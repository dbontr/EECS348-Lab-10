#include "double_string.hpp"
// Align fractional lengths
string af = a.fracPart, bf = b.fracPart;
size_t Lf = std::max(af.size(), bf.size());
padRight(af, Lf); padRight(bf, Lf);


// Add fractional from right to left
string rfrac(Lf, '0');
int carry = 0;
for (int i = static_cast<int>(Lf) - 1; i >= 0; --i) {
int da = af[i] - '0';
int db = bf[i] - '0';
int s = da + db + carry;
rfrac[i] = char('0' + (s % 10));
carry = s / 10;
}


// Align integer lengths
string ai = a.intPart, bi = b.intPart;
size_t Li = std::max(ai.size(), bi.size());
padLeft(ai, Li); padLeft(bi, Li);


string rint(Li, '0');
for (int i = static_cast<int>(Li) - 1; i >= 0; --i) {
int da = ai[i] - '0';
int db = bi[i] - '0';
int s = da + db + carry;
rint[i] = char('0' + (s % 10));
carry = s / 10;
}
if (carry) rint.insert(rint.begin(), char('0' + carry));


DecNum out{'+', rint, rfrac};
normalize(out);
return out;
}


DecNum subMagnitudeAssumingAGeqB(const DecNum& a, const DecNum& b) {
// Align fractional lengths
string af = a.fracPart, bf = b.fracPart;
size_t Lf = std::max(af.size(), bf.size());
padRight(af, Lf); padRight(bf, Lf);


// Subtract fractional: af - bf
string rfrac(Lf, '0');
int borrow = 0;
for (int i = static_cast<int>(Lf) - 1; i >= 0; --i) {
int da = (af[i] - '0') - borrow;
int db = (bf[i] - '0');
if (da < db) { da += 10; borrow = 1; } else borrow = 0;
int d = da - db;
rfrac[i] = char('0' + d);
}


// Align integer lengths
string ai = a.intPart, bi = b.intPart;
size_t Li = std::max(ai.size(), bi.size());
padLeft(ai, Li); padLeft(bi, Li);


string rint(Li, '0');
for (int i = static_cast<int>(Li) - 1; i >= 0; --i) {
int da = (ai[i] - '0') - borrow;
int db = (bi[i] - '0');
if (da < db) { da += 10; borrow = 1; } else borrow = 0;
int d = da - db;
rint[i] = char('0' + d);
}
// borrow must be zero here since |a| >= |b|


DecNum out{'+', rint, rfrac};
normalize(out);
return out;
}


DecNum add(const DecNum& x, const DecNum& y) {
// Handle signs
if (x.sign == y.sign) {
DecNum sum = addMagnitude(x, y);
sum.sign = x.sign; // both same
normalize(sum);
return sum;
}
// Different signs: compute |x| ? |y|
int cmp = cmpMagnitude(x, y);
if (cmp == 0) {
DecNum zero{'+', "0", ""};
return zero;
} else if (cmp > 0) { // |x| > |y|
DecNum d = subMagnitudeAssumingAGeqB(x, y);
d.sign = x.sign;
normalize(d);
return d;
} else {
DecNum d = subMagnitudeAssumingAGeqB(y, x);
d.sign = y.sign;
normalize(d);
return d;
}
}
