#include <iostream>
#include <algorithm>
#include <numeric>
#include "factorLU.h"
#include "matrix.h"

Vector getRowScales (const Matrix &A)
{
	Vector s(A.size(),0);
	for (int i=0;i<A.size();++i)
	{
		double maxElement = 0;
		for (int j=0;j<A[0].size();++j)
		{
			double element = std::abs(A[i][j]);
			if (element>maxElement)
				maxElement = element;
		}
		s[i] = maxElement;
	}
	return s;
}

void luStep(Matrix &A, const int k)
{
	const double A_kk = A[k][k];
	for (int i=k+1;i<A.size();++i)
	{
		double l_ik = A[i][k]/A_kk;
		for (int j=k+1;j<A[0].size();++j)
		{
			A[i][j]=A[i][j]-l_ik*A[k][j];
		}
		A[i][k]=l_ik;
	}
}

void pivotStep (Matrix &A, const int k, Vector &map, const Vector &s)
{
	int maxRow = k;
	double maxVal = A[k][k]/s[k];
	for (int i=k+1;i<A.size();++i)
	{
		double val = A[i][k]/s[i];
		if (val>maxVal)
			maxVal = val;
			maxRow = i;
	}
	std::swap(A[maxRow],A[k]);
	std::swap(map[maxRow],map[k]);
}

//Warning - modifies input
//Takes in a matrix, modifies the matrix to LU factored form, and returns a permutation map to be applied to inputs prior to back substitution
Vector factorLUWithPartialPivot (Matrix &A)
{
	Vector map(A.size());
    std::iota(map.begin(), map.end(), 0); //intialize to 0,1,...,n-1
	const Vector s = getRowScales(A);
	for (int k=0;k<A.size();++k)
	{
		pivotStep(A,k,map,s);
		luStep(A,k);
	}
	return map;
}

void printLU(const Matrix &m)
{
	//print L
	for (int i=0;i<m.size();i++)
	{
		std::cout << ((i==0) ? '[' : ' ');
		std::cout << "[";
		std::cout << ((i==0) ? 1 : m[i][0]);
		for (int j=1; j<m[i].size(); j++)
		{
			std::cout << ",";
			if (i>j)
				std::cout << m[i][j];
			else
				std::cout << ((i==j) ? 1 : 0);
		}
		std::cout << "]" << ((i==m.size()-1) ? ']' : ',') << std::endl;
	}

	//print U
	for (int i=0;i<m.size();i++)
	{
		std::cout << ((i==0) ? '[' : ' ');
		std::cout << "[";
		std::cout << ((i==0) ? m[i][0] : 0);
		for (int j=1; j<m[i].size(); j++)
			std::cout << "," << ((i<j) ? 0 : m[i][j]);
		std::cout << "]" << ((i==m.size()-1) ? ']' : ',') << std::endl;
	}
}

Matrix verifyLU(const Matrix &m, Vector p)
{
	Matrix L (m.size(),Vector(m.size(),0));
	Matrix U (m.size(),Vector(m.size(),0));
	for (int i=0;i<m.size();++i)
	{
		//populate L
		// L[i][0] = ((i==0) ? 1 : m[i][0]);
		for (int j=0; j<m[i].size(); j++)
		{
			if (i>j)
				L[i][j] = m[i][j];
			else
				L[i][j] = ((i==j) ? 1 : 0);
		}

		//populate U
		// U[i][0] = ((i==0) ? m[i][0] : 0);
		for (int j=0; j<m[i].size(); j++)
			U[i][j] = ((i>j) ? 0 : m[i][j]);
	}
	std::cout << "L = \n";
	printMatrix(L);
	std::cout << "U = \n";
	printMatrix(U);
	//multiply LU
	Matrix m2 = matrixMatrixProduct(L,U);

	//correct for earlier permutation
	for(int i=0;i<m.size();++i)
	{
		int p_i = p[i];
		if (p_i!=i)
		{
			std::swap(m2[p_i], m2[i]);
			std::swap(p[p_i],p[i]);
		}
	}
	std::cout << "LU = \n";
	printMatrix(m2);
	return m2;
}