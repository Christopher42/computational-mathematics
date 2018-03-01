//requires <vector>
#ifndef LAPLACIAN_H
#define LAPLACIAN_H
typedef std::vector<double> Vec;
typedef std::vector<std::vector<double>> Matrix;

void initF(int m, double(*f)(double,double), Vec& F);

//init AU=F, then solve for U
void initLaplace5 (int m, Matrix& A, Vec& U, Vec& F, double(*f)(double,double));

void initLaplace9 (int m, Matrix& A, Vec& U, Vec& F, double(*f)(double,double));

#endif