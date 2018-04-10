// GEtest.cpp
// Author: Isaac Stone
// Language: C++
//
// Synopsis: This file includes headers gaussElim.cpp to implement
// Guassin Elimination with back-substitution for an augmented matrix. The function
// gaussElim() takes a Matrix ( matrix.h ) as an argument and returns a
// solution to Ax=b in the form of a Vector ( vectorCode.h ). If no solution or 
// only the trivial solution exists, a message is printed 
// to the screen and the program exits.
//
// Check "gaassElim.cpp" for more information.

#include <vector>
#include <cstdlib>
#include "matrix.h"
#include "vectorCode.h"

Vector gaussElim( Matrix A );
