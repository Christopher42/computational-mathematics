**Routine Name:**           functionalIteration

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Description/Purpose:** This routine will approximate the a solution to the root finding problem f(x)=0, guaranteed within a user input tolerance. The given function f(x) must be a continuous function on one variable.

**Input:**
Double a give an initial guess at the solution.
Function f(x) gives a real-valued, continuous function on a single variable.
Double tol is an optional parameter giving the required precision. Defaults to 10^-8 if not otherwise specified.

**Output:**
Returns a double, giving the appoximated solution of f(x)=0. If the function fails to converge within 1000000 iterations, it will throw a notConvergentException.

**Usage/Example:**

In order to call the function functionalIteration, a target function f(x) must first be defined. Example usage code follows:

    #include <iostream>
    #include <cmath>
    #include "functionalIteration.h"

    double f(double x)
    {
        return 3.0*sin(10*x);
    }

    double g(double x)
    {
        return x*exp(-x);
    }

    int main(void)
    {
        double froot,groot;
        try{
            froot = functionalIteration(-0.00000001,f);
            std::cout << "Root of f(x) at x=" << froot << std::endl;
        }
        catch(notConvergentException& e){
            std::cout << "Root of f(x) could not be calculated, as series did not converge.\n";
        }

        froot = functionalIteration(0,f);
        std::cout << "Root of f(x) at x=" << froot << std::endl;

        groot = functionalIteration(1.05,g);
        std::cout << "Root of g(x) at x=" << groot << std::endl;

        return 0;
    }

Output from the lines above:

    Root of f(x) could not be calculated, as series did not converge.
    Root of f(x) at x=0
    Root of g(x) at x=-2.13696e-20

Function f() is poorly conditioned for this algorithm, as it has a root a zero, but a value very close to zero failed to converge to the solution. If one was determined to utilize functional iteration to find a root of f(x), it would be necessary to find a different function to iterate on.
The function g(x) has exactly one root, which is at x=0. Through testing, it was determined that any value in the range (-.6931,1.0603) would converge to the root, while any value outside of this range would never converge.
As has been observed, the boiler-plate solution of iterating "x_{k+1} = f(x_k) - x_k" does not produce stable convergence in a wide range for either function examined. If functional iteration is to be used to solve for a root of a function, it is highly recommended that a custom iteration function be determined and utilized.


**Implementation/Code:** The following is the code for functionalIteration(a,f,tol)

    //Finds an approximation of a root f(x)=0
    //Input: a = starting estimate, f = function, tol = maximum accceptable error
    //Output: double, approximation of some root of f(x)
    double functionalIteration(double a, double (*f)(double), double tol=pow(10,-8))
    {
        int maxIter = 1000000;
        double error = 10*tol; //force loop to execute at least once
        double x=a;
        int count=0;
        while (error>tol && ++count<maxIter)
        {
            //iterate on function x = f(x)-x
            double xprime = f(x)-x;
            error = std::abs(x-xprime);
            x = xprime;
        }
        if (count == maxIter)
            throw notConvergent;
        else
            return x;
    }

**Last Modified:** September/2017
