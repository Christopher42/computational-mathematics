**Routine Name:**           bisection_newton

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Description/Purpose:** This routine will approximate the a solution to the root finding problem f(x)=0, guaranteed within a user input tolerance, using the secant method.

**Input:**
Doubles a and b are initial guesses at location of the value.
Function f(x) is the function for which a root is to be found.
Function fprime(x) is the derivative of f(x).
Double tol dictates the required precision of an answer. Default to 1e-8 if not given.

**Output:**
Returns a single double, giving the appoximated solution of f(x)=0.
The method will instead throw a invalidIntervalException if improperly bracketed.

**Usage/Example:**

In order to call the method bisection_newton, a target function f(x) must first be defined. The function may then be called as follows:

      double f(double x) {return 3*x*sin(10*x); }
      for (int x=0; x<3; x++)
        std::cout << "bisection_newton estimate of root of f(x) is " << bisection_newton(x-.25,x+.25,f,fprime) << std::endl;

Function returns error for ranges around 0 and 2, due to improper bracketing.
Output from the intial value x=1:

      secant estimate of root of f(x) is 0.942478

The method is more restricted by the requirement for proper bracketing.


**Implementation/Code:** The following is the code for bisection_newton(a,b,f(),fprime(),tol)

    inline double newtonStep (double x, double (*f)(double), double (*fprime)(double))
    {
      return x - f(x)/fprime(x);
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

    double bisection_newton (double a, double b, double (*f)(double),
      double (*fprime)(double), double tol=pow(10,-8))
    {
      if (a>b) std::swap(a,b);
      if (f(a)*f(b)>0)
        throw invalidInterval;

      double err = tol*10;
      while (err>tol)
      {
        bisect_step(a,b,f,4);
        err = std::abs(a-b);
        double x = newtonStep((a+b)/2,f,fprime);
        if (a<=x and x<=b)
        {
          while (err>tol and a<=x and x<=b)
          {
            double x1 = newtonStep(x,f,fprime);
            err = std::abs(x1-x);
            x=x1;
          }
          if (tol>err)
            return x;
        }
      }
      return a;
    }

**Last Modified:** October/2017
