**Routine Name:** Secant

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in** "secant.h"

**Description/Purpose:** This routine will approximate the a solution to the root finding problem f(x)=0, guaranteed within a user input tolerance, using the secant method. Includes safety features such as checking for division by zero and maximum iteration limit.

**Input:**
Doubles x0 and x1 are initial guesses at location of the value.
Function f(x) is the function for which a root is to be found.
Integer maxiter give a user defined maximum number of iterations. Default to 100 if not given.
Double tol dictates the required precision of an answer. Default to 1e-8 if not given.

**Output:**
Returns a single double, giving the appoximated solution of f(x)=0.
The method will instead throw a notConvergentException if the method fails to converge within tol precision in given number of iterations.

**Usage/Example:**

In order to call the method secant, a target function f(x) must first be defined. The function may then be called as follows:
```C++
double f(double x) {return 3*x*sin(10*x); }
for (int x=0; x<3; x++)
    std::cout << "secant estimate of root of f(x) is " << safeNewton(x-.25,x+.25,f,fprime) << std::endl;
```

Output from the lines above:
```C++
secant estimate of root of f(x) is 1.35881e-08
secant estimate of root of f(x) is 1.25664
secant estimate of root of f(x) is 3.14159
```

It may be noted that fprime(0)=0 and this should cause the method to fail. The method corrects for this by setting the would-be zero value to tol, allowing divion to proceed. The calculated value is within the specified precision of zero.
Function f() has roots at x = `k*pi/10`, making the other calculated roots correct.


**Implementation/Code:** The following is the code for secant(x0,x1,f(),maxiter,tol)
```C++
double secant (double x0, double x1, double (*f)(double),
    int maxiter = 100, double tol=pow(10,-8))
{
    double err = 10*tol;
    double f0,f1;
    while (err>tol and --maxiter>0)
    {
        f0 = f(x0);
        f1 = f(x1);
        double fdiff = f1-f0;
        if (std::abs(fdiff) == 0)
        {
            fdiff = tol;
        }
        double x2 = x1 - f1*(x1-x0)/fdiff;
        x0=x1;
        x1=x2;
        err = std::abs(x1-x0);
    }
    if(maxiter == 0)
    {
        throw notConvergent;
    }
    return x1;
}
```
**Last Modified:** October/2017
