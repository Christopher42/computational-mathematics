// GEtest.cpp
// Author: Isaac Stone
// Language: C++
//
// Synopsis: This .h file implements Guassin Elimination with
// back-substitution for an augmented matrix. The function
// gaussElim() takes a Matrix ( matrix.h ) as an argument and returns a
// solution to Ax=b in the form of a Vector ( vectorCode.h ). If no solution or 
// only the trivial solution exists, a message is printed 
// to the screen and the program exits.

#include <vector>
#include <cstdlib>
#include "matrix.h"
#include "vectorCode.h"

using namespace std;

// Elimination step
void Elim( double x, Vector &a, Vector &b ) {
	
  for ( unsigned i = 0; i < a.size(); i++ )
	  a[i] = a[i] - ( x * b[i] );
}

Vector gaussElim( Matrix A ) {
	
  int i, j, p, n;
  double sum, xn, x;
  Vector tmp, sols;

  x = 0.0;
  p = 0;
  n = A.size();

  // Guassian Elimination
  for ( i = 0; i < (n - 1) ; i++ )
  {
	p = i;
	while( A[p][i] == 0 )
	{
	  p++;
	  if ( p >  n )
	  {
		printf( "No solution or trivial solution\n" );
		exit(1);
	  }
	}
	
	// Swap rows
	if ( p != i ) {
	  tmp = A[p];
	  A[p] = A[i];
	  A[i] = tmp;
	}
		
	for ( j = i+1; j < n; j++ )
	{
	  x = A[j][i] / A[i][i];
	  Elim( x, A[j], A[i] );
	}
  }

  // Test for no solution
  if ( A[ n - 1 ][ n - 1 ] == 0 )
  {
    printf( "No solution or trivial solution\n" );
	exit(1);
  }
 
  // Perform back-substitution
  sols.resize( n, 0 );
  
  xn = A[n-1][n] / A[n-1][n-1];
  sols[n-1] = xn;
  
  for ( int i = n-1; i >= 0; i-- )
  {
	sum = 0;
	for ( j = i+1; j < n+1; j++ ) {
	  sum += ( A[i][j] * sols[j] );
	}
	xn = ( A[i][n] - sum ) / A[i][i];
	sols[i] = xn;
  }

  return sols;
}
