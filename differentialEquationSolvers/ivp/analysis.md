See PDF file "differentialEquationSolvers/ivp/IVP_Solvers.pdf" for performance comparision.

Note that Adams34 method, while technically only guaranteed to be 3rd order convergence, generally works as well or better than RK-4. Implicit Euler failed for example 7.2, as problem fell outside of stability bounds.

While RK-4 makes more funciton calls, for the functions tested, this made no measurable difference in operation time when compared to other methods.