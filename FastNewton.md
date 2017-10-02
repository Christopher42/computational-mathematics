**Routine Name:**           FastNewton

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Description/Purpose:** This routine will approximate the a solution to the root finding problem f(x)=0, guaranteed within a user input tolerance, using Newton's method. Safety features not included.

**Input:**
Double x is an initial guess at location of the value.
Function f(x) is the function for which a root is to be found.
Function fprime(x) is the derivative of the target function.
Double tol dictates the required precision of an answer. Default to 1e-8 if not given.

**Output:**
Returns a single double, giving the appoximated solution of f(x)=0.

**Usage/Example:**

In order to call the method fastNewton, a target function f(x) and it's derivative fprime(x) must first be defined. The function may then be called as follows:

      double f(double x) {return 3*x*sin(10*x); }
      double fprime(double x){ return 3*sin(10*x) + 30*x*cos(10*x); }
      for (int x=0; x<3; x++)
        std::cout << "fast newton estimate of root of f(x) is " << fastNewton(x,f,fprime) << std::endl;

Output from the lines above:

      fast newton estimate of root of f(x) is nan
      fast newton estimate of root of f(x) is 0.942478
      fast newton estimate of root of f(x) is 1.88496

It may be noted that the given root with initial value of x=0 was "nan", or, "not a number". This occured as fprime(0) = 0, and division by zero is not allowed. This will be corrected in the safeNewton implementation.
Function f() has roots at x = k*pi/10, making the other calculated roots correct.


**Implementation/Code:** The following is the code for bisect(a,b,f(),tol)

    double fastNewton (double x, double (*f)(double), double (*fprime)(double),
      double tol=pow(10,-8))
    {
      double x1 = x - f(x)/fprime(x);
      while (std::abs(x1-x)>tol)
      {
        x=x1;
        //apply the newton step
        x1 = x - f(x)/fprime(x);
      }
      return x1;
    }

**Last Modified:** September/2017
