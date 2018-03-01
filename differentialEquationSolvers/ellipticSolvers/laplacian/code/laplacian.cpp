#include <vector>
#include <iostream>
typedef std::vector<double> Vec;
typedef std::vector<std::vector<double>> Matrix;

void initF(int m, double(*f)(double,double), Vec& F)
{
	F = Vec(m*m,0);
	for (int i=0;i<m;++i)
	{
		for (int j=0;j<m;++j)
		{
			double x = (i+1.0)/(m+2.0);
			double y = (j+1.0)/(m+2.0);
			int index = i+j*m;
			F[index] = f(x,y);
		}
	}
}

//init AU=F, then solve for U
void initLaplace5 (int m, Matrix& A, Vec& U, Vec& F, double(*f)(double,double))
{
	A = Matrix(m*m,Vec(m*m,0));
	U = Vec(m*m,0);
	for (int i=0;i<U.size();++i)
	{
		if(i%2==1)
			U[i]=1;
		else
			U[i]=-1;
	}

	initF(m,f,F);
	for (int i=0;i<F.size();++i)
	{
		F[i]*=(m+2)*(m+2);
	}

	//init A
	for (int i=0;i<m;++i)
	{
		for (int j=0;j<m;++j)
		{
			int index = i+j*m;
			A[index][index] = -4;
			if (i+1<m)
				A[index][index+1] = 1;
			if (i-1>=0)
				A[index][index-1] = 1;
			if (j+1<m)
				A[index][index+m] = 1;
			if (j-1>=0)
				A[index][index-m] = 1;
		}
	}
}

void initLaplace9 (int m, Matrix& A, Vec& U, Vec& F, double(*f)(double,double))
{
	A = Matrix(m*m,Vec(m*m,0));
	U = Vec(m*m,0);
	for (int i=0;i<U.size();++i)
	{
		if(i%2==1)
			U[i]=1;
		else
			U[i]=-1;
	}
	initF(m,f,F);
	for (int i=0;i<F.size();++i)
	{
		F[i]*=6*(m+2)*(m+2);
	}

	//init A
	for (int i=0;i<m;++i)
	{
		for (int j=0;j<m;++j)
		{
			int index = i+j*m;
			A[index][index] = -20;
			if (i+1<m)
				A[index][index+1] = 4;
			if (i-1>=0)
				A[index][index-1] = 4;
			if (j+1<m)
			{
				A[index][index+m] = 4;
				if (i+1<m)
					A[index][index+m+1] = 1;
				if (i-1>=0)
					A[index][index+m-1] = 1;
			}
			if (j-1>=0)
			{
				A[index][index-m] = 4;
				if (i+1<m)
					A[index][index-m+1] = 1;
				if (i-1>=0)
					A[index][index-m-1] = 1;
			}
		}
	}
}