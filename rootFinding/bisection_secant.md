**Routine Name:** secant

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in** "hybrid.h"

**Description/Purpose:** This routine will approximate the a solution to the root finding problem f(x)=0, guaranteed within a user input tolerance, using a hybrid of bisection and secant methods. The algorithm will apply the secant method until finding an interval that will converge under the secant method, at which point, it runs the faster secant method to completion.

**Input:**
Doubles a and b are initial guesses at location of the value.
Function f(x) is the function for which a root is to be found.
Double tol dictates the required precision of an answer. Default to 1e-8 if not given.

**Output:**
Returns a single double, giving the appoximated solution of f(x)=0.

**Usage/Example:**

In order to call the method, a target function f(x) must first be defined. The function may then be called as follows:

```C++
double f(double x) {return 3*x*sin(10*x); }
for (int x=0; x<3; x++)
    std::cout << "bisection_secant estimate of root of f(x) is " << bisection_secant(x-.25,x+.25,f) << std::endl;
```

The method fails on values 0 and 2, throwing an invalid interval exception.
The output from the range (.75,1.25) is
```C++
bisection_secant estimate of root of f(x) is 0.942478
```
            
Note that the method fails in a situation where the pure secant method would succeed (see secant method documentation for example). A noteable downside to this method is the requirement of proper bracketing.


**Implementation/Code:** The following is the code for bisection_secant(x0,x1,f(),tol)
```C++
inline double secantStep (double x0, double x1, double (*f)(double))
{
    return x1 - (f(x1)*(x1-x0))/(f(x1)-f(x0));
}

void bisect_step (double& a, double& b, double (*f)(double), int iterations)
{
        for(int i=0; i<iterations; i++)
        {
                double c = (a+b)*.5;
                //Divide the interval at the midpoint c
                if (f(a)*f(c)<0)
                        b=c;
                else
                        a=c;
        }
}

double bisection_secant (double a, double b, double (*f)(double),
    double tol=pow(10,-8))
{
    if (a>b) std::swap(a,b);
    if (f(a)*f(b)>0)
        throw invalidInterval;

    double err = tol*10;
    while (err>tol)
    {
        bisect_step(a,b,f,4);
        err = std::abs(a-b);
        double x1 = secantStep(a,b,f);
        if (a<=x1 and x1<=b)
        {
            double x0 = b;
            while (err>tol)
            {
                double x2 = secantStep(x0,x1,f);
                err = std::abs(x2-x1);
                x0=x1;
                x1=x2;
            }
            return x1;
        }
    }
    return a;
}
```
**Last Modified:** October/2017
