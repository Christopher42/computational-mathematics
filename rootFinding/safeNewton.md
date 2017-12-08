**Routine Name:** SafeNewton

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in** "newton.h"

**Description/Purpose:** This routine will approximate the a solution to the root finding problem f(x)=0, guaranteed within a user input tolerance, using Newton's method. Includes safety features such as checking for division by zero and maximum iteration limit.

**Input:**
Double x is an initial guess at location of the value.
Function f(x) is the function for which a root is to be found.
Function fprime(x) is the derivative of the target function.
Integer maxiter give a user defined maximum number of iterations. Default to 100 if not given.
Double tol dictates the required precision of an answer. Default to 1e-8 if not given.

**Output:**
Returns a single double, giving the appoximated solution of f(x)=0.
The method will instead throw notConvergentError if convergence does not occur within tol limits in alloted number of iterations.

**Usage/Example:**

In order to call the method safeNewton, a target function f(x) and it's derivative fprime(x) must first be defined. The function may then be called as follows:
```C++
double f(double x) {return 3*x*sin(10*x); }
double fprime(double x){ return 3*sin(10*x) + 30*x*cos(10*x); }
for (int x=0; x<3; x++)
    std::cout << "safe newton estimate of root of f(x) is " << safeNewton(x,f,fprime) << std::endl;
```

Output from the lines above:
```C++
safe newton estimate of root of f(x) is -5e-09
safe newton estimate of root of f(x) is 0.942478
safe newton estimate of root of f(x) is 1.88496
```

It may be noted that fprime(0)=0 and this should cause the method to fail. The method corrects for this by perturbing the value of x by tol, preventing division by zero. The value -5e-09 is within precision 1e-09 of zero.
Function f() has roots at `x = k*pi/10`, making the other calculated roots correct.


**Implementation/Code:** The following is the code for safeNewton(x,f(),fprime(),maxiter,tol)
```C++
double safeNewton (double x, double (*f)(double), double (*fprime)(double),
        int maxiter = 100, double tol=pow(10,-8))
{
    double err = 10*tol;
    while (--maxiter>0 and err>tol)
    {
        if (fprime(x)==0)
        {
            //perturb value to avoid division by zero
            x-=tol;
            err+= tol;
            continue;
        }
        else
        {
            double x1=newtonStep(x,f,fprime);
            err = std::abs(x1-x);
            x=x1;
        }
    }
    if(maxiter == 0)
    {
        throw notConvergent;
    }
    return x;
}
```
**Last Modified:** October/2017
