EECS 348 - Lab 10: String-Based Calculator (C++)


## Overview
A tiny calculator that validates decimal numbers in **string form** and adds them **without converting to built-in numeric types**. It reads pairs of candidate numbers from a user-specified file (one pair per line), validates each token, and if both are valid, prints their sum; otherwise it reports which token(s) are invalid and continues.


### Valid number format (lab spec)
- Optional leading sign: `+` or `-`
- Then **at least one digit**
- Optional decimal point `.`; if present, **must** have at least one digit on **both** sides
- No other characters allowed
- Examples: `1`, `1.0`, `+1.0`, `+0001.0`, `-0001.005`
- Invalid: `A`, `+-1`, `-5.`, `-5.-5`


### What’s inside
- `src/double_string.hpp` — string number parsing, validation, normalization, and arithmetic on magnitudes
- `src/double_string.cpp` — implementation
- `src/main.cpp` — CLI; reads file, tokenizes lines, validates, adds, prints
- `Makefile` — build & run helpers
- `tests/testcases.txt` — 30 sample lines


### Build
```bash
make
```


### Run
Provide the path to your test file as the first argument. If omitted, the program will prompt for it.
```bash
./bin/string_calc tests/testcases.txt
```


### Output format
For each input line, either:
- `SUM: <a> + <b> = <result>` for valid pairs, or
- `INVALID: <token>` (prints one or both invalid tokens)


Normalization rules on output:
- Integer part has no leading zeros (except a single `0` if value is zero)
- Fraction has no trailing zeros; the decimal point is removed if the fraction becomes empty
- `-0` becomes `0`
