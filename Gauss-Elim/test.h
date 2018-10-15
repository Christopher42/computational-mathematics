#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

void Swap( vector <double> &a, vector <double> &b ) {
	
	vector <double> tmp;
	tmp = a;
	a = b;
	b = tmp;
}

void Elim( double x, vector <double> &a, vector <double> &b ) {
	
		for ( unsigned i = 0; i < a.size(); i++ )
			a[i] = a[i] - ( x * b[i] );
}

int gaussElim( vector< vector <double> > &m, vector <double> &sols ) {
	
	unsigned int i, j, p, n, iterations;
	double sum, xn, x;

	x = 0.0;
	p = 0;
	iterations = 0;
	n = m.size();
	/*
	for ( unsigned i = 0; i < m.size(); i++ )
	{
		for ( unsigned j = 0; j < m[0].size(); j++ )
		{
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl; 
	*/

	for ( i = 0; i < n - 1 ; i++ )
	{
	  iterations++;

	  p = i;
	  while( m[p][i] == 0 )
	  {
		p++;
		if ( p > n )
		{
		  cout << "No solution or trivial solution" << endl;
		  return 0;
		}
	  }
	  
	  if ( p != i )
		Swap( m[p], m[i] );
		  
	  for ( j = i+1; j < n; j++ )
	  {
		x = m[j][i] / m[i][i];
		Elim( x, m[j], m[i] );
	  }
	}
	
	if ( m[ n - 1 ][ n - 1 ] == 0 )
	{
	  cout << "No solution or trivial solution" << endl;
		return 0;
	}
	
	xn = m[n-1][n] / m[n-1][n-1];
	sols.resize( n, 0 );
	sols[n-1] = xn;
	
	for ( i = n-1; i >= 0; i-- )
	{
	  sum = 0;
	  for ( j = i+1; j < n+1; j++ )
		sum += m[i][j] * sols[j];
	  xn = ( m[i][n] - sum ) / m[i][i];
	  sols[i] = xn;
	}

	for ( i = 0; i < sols.size(); i++ )
	  cout << - sols[i] << " ";
	 
	return iterations;
}
