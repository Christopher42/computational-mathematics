#include <algorithm>
#include <vector>
#include "tridiag.h"

using std::vector;

vector<vector<double>> convertToSquare (TridiagSys s)
{
	vector<vector<double>> r();
	for int (i=0;i<s.n;++i)
	{
		if (i>0)
			r[i][i-1] = s.lower[i];
		r[i][i] = s.main[i];
		if (i+1<s.n)
			r[i+1][i] = s.upper[i];
	}
	return r;
}

TridiagSys initSimpleElliptic(int m, double a, double b, double (*f)(double), double u_a, double u_b)
{
	TridiagSys system;
	system.n=m;
	system.main = std::vector<double>(m,-2);

	system.upper = std::vector<double>(m,1);
	system.upper[m-1]=0;

	system.lower = std::vector<double>(m,1);
	system.lower[0]=0;

	double h = 1.0/(1+m);
	std::vector<double> mesh(m);
	std::vector<double> bv(m);
	for(int i=0;i<m;++i)
	{
		mesh[i]=((b-a)*(i+1))/(m+1);
		bv[i]=f(mesh[i])/(h*h);
	}
	bv[0]-= u_a;
	bv[m-1]-= u_b;
	system.b = bv;
	system.mesh = mesh;
	return system;
}

TridiagSys initElliptic(int m, double a, double b, double (*f)(double), double (*k)(double), double u_a, double u_b)
{
	TridiagSys system;
	system.n=m;

	std::vector<double> mesh(m);
	std::vector<double> bv(m);
	for(int i=0;i<m;++i)
	{
		mesh[i]=((b-a)*(i+1))/(m+1);
		bv[i]=f(mesh[i])/((1+m)*(1+m)); //times h^2
	}
	bv[0]-= u_a;
	bv[m-1]-= u_b;
	system.b = bv;
	system.mesh = mesh;

	system.main = std::vector<double>(m,-2);

	system.upper = std::vector<double>(m,0);
	system.lower = std::vector<double>(m,0);
	system.lower[0]=k((u_a+mesh[0])/2);
	system.upper[m-1]=k((mesh[m-1]+u_b)/2);
	for (int i=0;i<m-2;++i)
	{
		system.lower[i+1]=system.upper[i]=k((mesh[i]+mesh[i+1])/2);
		system.main[i]=(system.lower[i]+system.upper[i])/2;
	}
	system.lower[0]=0;
	system.upper[m-1]=0;

	system.lower = std::vector<double>(m,1);
	system.lower[0]=0;

	return system;
}

std::vector<double> thomasAlg(TridiagSys& A)
{
	int n = A.n;
	std::vector<double> x = A.b;
	std::vector<double> c = A.upper;

	c[0]/= A.main[0];
	for (int i=0;i<n;++i)
	{
		c[i]/=(A.main[i]-A.lower[i]*c[i-1]);
	}

	x[0] /=A.main[0];
	for (int i=0;i<n;++i)
	{
		x[i]=(x[i]-A.lower[i]*x[i-1])/(A.main[i]-A.lower[i]*c[i-1]);
	}

	return x;
}

void luTridiag(TridiagSys& A)
{
	int n=A.n;
	for(int i=1;i<n;++i)
	{
		A.lower[i]/=A.main[i-1];
		A.main[i]-=A.lower[i]*A.upper[i-1];
	}
	return;
}

std::vector<double> evalLUTridiag(const TridiagSys& A, const std::vector<double>& b)
{
	std::vector<double> sol = b;
	for (int i=1;i<A.n;++i)
	{
		sol[i]-=A.lower[i]*sol[i-1];
	}
	sol[A.n-1]/=A.main[A.n-1];
	for(int i=A.n-2;i>=0;--i)
	{
		sol[i]=(sol[i]-A.upper[i]*sol[i+1])/A.main[i];
	}
	return sol;
}

std::vector<double> jacobiTridiag(TridiagSys& A, int max_iter, double tol)
{
	int n=A.n;

	double err=10*tol;
	std::vector<double> x(A.n);
	std::vector<double> xold=x;
	int k=0;

	while(k++<max_iter and err>tol*tol)
	{
		x=A.b;
		for (int i=0;i<n-1;++i)
		x[i]-=A.lower[i]*xold[i+1];
		for (int i=1;i<n;++i)
		x[i]-=A.upper[i]*xold[i-1];
		for(int i=0;i<n;++i)
		x[i]/=A.main[i];

		err=0.0;
		for (int i=0;i<n;++i)
		err+=(x[i]-xold[i])*(x[i]-xold[i]);
		xold=x;
	}
	return x;
}