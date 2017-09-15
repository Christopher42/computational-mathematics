**Routine Name:**           bisect

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Description/Purpose:** This routine will approximate the a solution to the root finding problem f(x)=0, guaranteed within a user input tolerance. The given function f(x) must be a continuous function on one variable.

**Input:**
Doubles a and b give a bracketed range containing a root, with f(a)*f(b)<0.
Function f(x) gives a real-valued, continuous function on a single variable
Double tol is an optional parameter giving the required precision. Defaults to 10^-8 if not otherwise specified.

**Output:**
Returns a single double, giving the appoximated solution of f(x)=0.

**Usage/Example:**

In order to call the function bisect, a target function f(x) must first be defined. The function may then be called as follows:

      double g(double x){ return (x-2)*(x+3); }
      double tol = pow(10,-5);
      std::cout << bisect(-10,0,g) << std::endl; //print function
      std::cout << bisect(0,10,g,tol) << std::endl;
      std::cout << bisect(-5,4,g,tol) << std::endl;

Output from the lines above:

      -2
      3
      -6

Function g() has roots at -2 and 3, given by the first two outputs. Note that tol uses default value if not specified.
As the third range did not properly bracket an output (f(a)*f(b) > 0), the function returned an error value outside range.


**Implementation/Code:** The following is the code for bisect(a,b,f(),tol)

      #include <cmath> //required for log(x), pow(x,e)
      double bisect(double a, double b, double (*f)(double), double tol=pow(10,-8))
      {
          double fa = f(a);
          double fb = f(b);
          //if no sign change in range, method fails. Return an error value outside of range
          if (fa*fb > 0)
              return std::min(a,b)-1.0;

          //compute iterations required to guarantee accuracy within tol
          int maxiter = (log(std::abs(a-b)/tol) / log(2)) + 1;

          //bisect the interval repeatedly to find location of root
          for(int i=0; i<maxiter; i++)
          {
              //calculate f() at the midpoint c
              double c = (a+b)*.5;
              double fc = f(c);
              //Divide the interval at the midpoint c
              if (fa*fc<0)
              {
                  b=c;
                  fb=fc;
              }
              else
              {
                  a=c;
                  fa=fc;
              }
          }
          return a;
      }

**Last Modified:** September/2017
