#include <algorithm>
#include <vector>

struct TridiagSys {
int n;
std::vector<double> main;
std::vector<double> upper;
std::vector<double> lower;
std::vector<double> mesh;
std::vector<double> b;
}

TridiagSys initSimpleElliptic(int m, double a, double b, double (f*)(double), double u_a, double u_b)
{
TridaigSys system;
system.n=m;
system.main = std::vector<double>(m,-2);

system.upper = std::vector<double>(m,1);
system.upper[m-1]=0;

system.lower = std::vector<double>(m,1);
system.lower[0]=0;

double h = 1.0/(1+m);
std::vector<double> mesh(m);
std::vector<double> b(m);
for(int i=0;i<m;++i)
{
mesh[i]=((b-a)*(i+1))/(m+1)
b[i]=f(mesh[i])/(h*h);
}
b[0]-= u_a;
b[m-1]-= u_b;
system.b = b;
system.mesh = mesh;
return system;
}

std::vector<double> thomasAlg(TridiagSys A)
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
x[i]=(x[i]-A.lower[i]*x[i-1])/(A.main[i]-A.lower[i]*c[i-1];
}

return x;
}

void luTridiag(TridiagSys A)
{
int n=A.n;
for(int i=1;i<n;++i)
{
lower[i]/=middle[i-1];
main[i]-=lower[i]*upper[i-1];
}
return;
}

std::vector<double> evalLUTridiag(TridiagSys A, std::vector b)
{
std::vector<double> sol = b;
for (int i=1;i<A.n;++i)
{
sol[i]-=A.lower[i]*sol[i-1];
}
sol[n-1]/=A.middle[n-1];
for(int i=n-2;i>=0;--i)
{
sol[i]=(sol[i]-A.upper[i]*sol[i+1])/A.middle[i];
}
return sol;
}

std::vector<double> jacobiTridiag(TridiagSys A, int maxIter, double tol)
{
int n=A.n;

double err=10*tol;
std::vector<double> x(A.n);
std::vector<double> xold=x;
int k=0;

while(k++<maxiter and err>tol*tol)
{
x=A.b;
for (int i=0;i<n-1;++i)
x[i]-=A.lower[i]*xold[i+1];
for (int i=1;i<n;++i)
x[i]-=A.upper[i]*x_old[i-1];
for(int i=0;i<n;++i)
x[i]\=A.main[i];

err=0.0;
for (int i=0;i<n;++i)
err+=(x[i]-xold[i])*(x[i]-xold[i]);
xold=x;
}
return x;
}
