// GEtest.cpp
// Author: Isaac Stone
// Language: C++
//
// Synopsis: This .h implements mat_gen() which  generates a pseudorandom augmented
// matrix ( it may be solvable or not ) and returns as a Matrix ( "matrix.h" ).
// Size of the matrix may be changed by modifying i and j limiting values within
// for loops.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "matrix.h"
#include <random>
#include <chrono>

using namespace std;

// set up random number generator
default_random_engine dre (chrono::steady_clock::now().time_since_epoch().count());

int random ( int lim ) {
  uniform_int_distribution<int> uid {0,lim};
  return uid(dre);
}

Matrix mat_gen() {

  int i, j;
  double x;
  Matrix M;
  vector <double> row;

  // seed generator
  srand( time(NULL) );

  M.clear();

  for (  i = 0; i < 5; i++ ) {

    row.clear();
	for ( j = 0; j < 6; j++ ) {
	  x = random(20);
	  row.push_back( x );
	}
    M.push_back( row );
  }

  return M;
}
