### Gaussian Elimination and Back-Substution Algorithm - gaussElim.h

#### Author: Isaac Stone, University of Tennessee Undergrad of Computer Science

gaussElim.h - Included is gaussElim.h, which implements the Gaussian Elimination and back-substituion method for an augmented matrix. The functionality is fairly simple. The function gaussElim() can be called by any c++ program that includes "gaussElim.h". It takes as its only argument a Matrix ( described in matrix.cpp ) and returns a Vector ( described in vectorCode.cpp ) that is the solution to Ax=b. If no solution exists, or only the trivial solution exists, the program prints an error and exits. 

##### Other files worth noting:

mat_gen.h - Generates an augmented matrix using pseudorandom values. It returns a Matrix and can be included via "mat_gen.h". For more, see commments in file.

GEtest.cpp - Used to test gaussElim.h with various inputs from mat_gen.h.

makefile - If working on a linux systems, make sure all files are in working directory and type "make" to compile.
 
iterativeSolvers.h, iterativeSolver.cpp, matrix.h, matrix.cpp, vectorCode.h, VectorCode.cpp -
All these files are dependencies for Matrix and Vector data structures needed for gaussElim.h and mat_gen.h to function as-is. They are written and developed by Christopher Johnson and obtained via GitHub at:

### https://github.com/Christopher42/computational-mathematics

where extensive documentation can be found, along with examples and testing information.

Project was compiled on a linux machine using g++ -std=11 and was produced under the GNU GeneralPublic License, version 3. Feel free to modify, include, and improve gaussElim.h and mat_gen.h under the GGPL. Thank you. 

Acknowledgements to Christopher Johnson, the author of the computational-mathematics repository on GitHhub.