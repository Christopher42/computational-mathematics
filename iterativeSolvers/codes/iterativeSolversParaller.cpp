#include "matrix.h"
#include "vectorCode.h"
#include "iterativeSolvers.h"

int jacobi(Matrix const &A, Vector const &b, Vector & x, int maxIter, double tol)
{
	int n = A.size();
	if (maxIter == 0) //makes default maxIter=n
		maxIter = n;
	double err = 10*tol;
	Vector x_old = x;
	int k=0;

	while (k++<maxIter and err>tol*tol)
	{
		// x = D^-1((L+U)x-b)
		for (int i=0;i<n;++i)
		{
			double sum = 0.0;
			for (int j=0;j<i;++j)
				sum+=A[i][j]*x_old[j];
			for (int j=i+1;j<n;++j)
				sum+=A[i][j]*x_old[j];
			x[i]=(b[i]-sum)/A[i][i];
		}

		// err = error^2 = L2err(x,x_old)^2
		err = 0.0;
		for (int i=0;i<n;++i)
			err += (x[i]-x_old[i])*(x[i]-x_old[i]);
		x_old = x;
	}
	return k;
}

int gaussSeidel (Matrix const &A, Vector const &b, Vector & x, int maxIter, double tol)
{
	int n = A.size();
	if (maxIter == 0)
		maxIter = n;
	double err = 10*tol;
	Vector x_old = x;
	int k=0;

	while (k++<maxIter and err>tol*tol)
	{
		for (int i=0;i<n;++i)
		{
			double sum = 0;
			for (int j=0;j<i;++j)
				sum+=A[i][j]*x[j];
			for (int j=i+1;j<n;++j)
				sum+=A[i][j]*x[j];
			x[i]=(b[i]-sum)/A[i][i];
		}

		// err = error^2 = L2err(x,x_old)^2
		err = 0.0;
		for (int i=0;i<n;++i)
			err += (x[i]-x_old[i])*(x[i]-x_old[i]);
		x_old = x;
	}
	return k;
}

int steepestDescent (Matrix const &A, Vector const &b, Vector & x, int maxIter, double tol)
{
	int n = A.size();
	int k=0;
	if (maxIter == 0)
		maxIter = n;
	//r_0 = b - Ax
	Vector r = matrixVectorProduct(A,x);
	for (int i=0;i<n;++i)
		r[i] = b[i]-r[i];
	//delta = ||x||_2^2
	double delta = dotProduct(r,r);
	//b_delta = ||b||_2^2
	double b_delta = dotProduct(b,b);
	Vector p = r;

	while (k++<maxIter and delta>tol*tol*b_delta)
	{
		//s_k = A*p_k
		Vector s(n,0);
		for (int i=0;i<n;++i)
			for (int j=0;j<n;++j)
				s[i]+=A[i][j]*p[j];
		//alpha_k = delta_k / (r_k \dot s_k)
		double alpha = 0;
		for (int i=0;i<n;++i)
			alpha += r[i]*s[i];
		alpha = delta/alpha;
		//x_k+1 = x_k + alpha_k*p_k
		for (int i=0;i<n;++i)
			x[i] += alpha*p[i];
		//r_k+1 = r_k - alpha_k*s_k
		for (int i=0;i<n;++i)
			r[i] -= alpha*s[i];
		//delta_k+1 = ||r_k+1||_2^2
		delta = 0;
		for (int i=0;i<n;++i)
			delta+=r[i]*r[i];
		p=r;
	}
	return k;
}

int conjugateGradient (Matrix const &A, Vector const &b, Vector & x, int maxIter, double tol)
{
	int n = A.size();
	if (maxIter == 0)
		maxIter = n;
	//r_0 = b - Ax
	Vector x1(n,0);
	Vector r = matrixVectorProduct(A,x);
	for (int i=0;i<n;++i)
		r[i] = b[i]-r[i];
	//delta = ||r||_2^2
	double delta = dotProduct(r,r);
	//b_delta = ||b||_2^2
	double b_delta = dotProduct(b,b);
	
	int k=0;
	Vector p = r;

	while (k++<maxIter and delta>tol*tol*b_delta)
	{
		//s_k = A*p_k
		Vector s(n,0);
		for (int i=0;i<n;++i)
			for (int j=0;j<n;++j)
				s[i]+=A[i][j]*p[j];
		//alpha_k = delta_k / (p_k \dot s_k)
		double alpha = 0;
		for (int i=0;i<n;++i)
			alpha += p[i]*s[i];
		alpha = delta/alpha;
		//x_k+1 = x_k + alpha_k*p_k
		//r_k+1 = r_k - alpha_k*s_k
		for (int i=0;i<n;++i)
		{
			x1[i] = x[i] + alpha*p[i];
			r[i] = r[i] - alpha*s[i];
		}
			
		//delta_k+1 = ||r_k+1||_2^2
		double delta_new = 0;
		for (int i=0;i<n;++i)
			delta+=r[i]*r[i];
		//p_k+1 = r_k+1 + (delta_k+1/delta_k)p_k
		for (int i=0;i<n;++i)
			p[i]=r[i]+(delta_new/delta)*p[i];
		delta = delta_new;
		x = x1;
	}
	return k;
}

int bonjugateGradient(Matrix const &A, Vector const &b,
        Vector &x0, int maxIter, double tol)
{   
    int n = b.size();
    if (maxIter == 0)
    	maxIter = n;
    Vector x1(n,0);
    Vector r0(n,0);
   
    Vector Ax0 = matrixVectorProduct(A, x0);
   
    for(int i = 0; i < n; i ++){
        r0[i] = b[i] - Ax0[i];
    }
   
    double delta0 = dotProduct(r0,r0);
    double b_delta = dotProduct(b,b);
   
    int k = 0;
    
    Vector p0 = r0;
   
    while(delta0 > tol*tol*b_delta and k < maxIter){
       
        Vector s = matrixVectorProduct(A, p0);
       
        double alpha = delta0/dotProduct(p0,s);
     
        for(int i = 0; i < n; i++){
            x1[i] = x0[i] + alpha*p0[i];
            r0[i] = r0[i] - alpha*s[i];
        }
       
        double delta1 = dotProduct(r0, r0);
       
        for(int i = 0; i < n; i++){
            p0[i] = r0[i] + (delta1/delta0)*p0[i];
        }
        
        k++;
        
        delta0 = delta1;
        x0 = x1;
        
    }
    return k;
}