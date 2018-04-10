// GEtest.cpp
// Author: Isaac Stone
// Language: C++
//
// Synopsis: This program simply tests the return
// value of the gaussElim() function described in
// "gaussElim.h". The mat_gen() function generates
// an augmented matrix that is stored into A. Both 
// the matrix and the solution to Ax=b are printed
// to the screen

#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "vectorCode.h"
#include "mat_gen.h"
#include "gaussElim.h"

using namespace std;

int main(  int argc, char **argv ) {

  Matrix A;
  vector<double> a_sols;
  
  A = mat_gen();
  a_sols.resize( A.size(), 0 );
  
  // Perform Gussian Elimination with 
  // back substitution
  a_sols = gaussElim( A );

  // Print augmented matrix A
  printMatrix(A);
  printf( "\n" );

  // Printf solutions to Ax=b
  printVector( a_sols );

  return 0;
}
