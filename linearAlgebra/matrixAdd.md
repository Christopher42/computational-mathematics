**Routine Name:** matrixAdd

**Author:** Christopher Johnson

**Language:** C++11. Tested with g++ compiler.

**Declared in** "matrix.h"

**Description/Purpose:** 
Computes the sum of two matrices.

**Input:**
Matrix a and Matrix b, where Matrix is a typedef of `std::vector<std::vector<double>>`.

**Output:**
Returns a Matrix, of size equal to the input matrices.

**Usage/Example:**

Two Matrices must first be defined, and then the method may be called.
```C++
Matrix a(5, Vector{-2,-1,0,1,2}); \\Creates a vector with 5 rows of [-2,-1,0,-1,-2]
Matrix b(5, Vector(5,1)); \\5*5 matrix of all ones
std::cout << "The matrix sum A + B is \n";
printMatrix(matrixAdd(a,b));
```
Output from the lines above:
```c++
The matrix sum A + B is
[[-1,0,1,2,3],
[-1,0,1,2,3],
[-1,0,1,2,3],
[-1,0,1,2,3],
[-1,0,1,2,3]]
```


**Implementation/Code:** The following is the code for matrixAdd(a,b)
```c++
Matrix matrixAdd(Matrix a, Matrix b)
{
    int n = a.size();
    int m = a[0].size();
    Matrix sol (m, Vector(n,0));

    for (int i=0;i<n;++i)
        for (int j=0;j<m;++j)
        sol[i][j] = a[i][j] + b[i][j];

    return sol;
}
```
**Last Modified:** October/2017
