**Routine Name:** matrixScale

**Author:** Christopher Johnson

**Language:** C++11. Tested with g++ compiler.

**Declared in** "matrix.h"

**Description/Purpose:** 
Multiplies matrix by scalar

**Input:**
Matrix a and double s, where Matrix is a typedef of `std::vector<std::vector<double>>`.

**Output:**
Returns a Matrix, of size equal to the input matrix.

**Usage/Example:**

A Matrix must first be defined, and then the method may be called.
```C++
Matrix b(5, Vector(5,1)); \\5*5 matrix of all ones
double s = 5.1;
std::cout << "B * s is\n";
printMatrix(matrixScale(b,s));
```
Output from the lines above:
```c++
B * s is
[[5.1,5.1,5.1,5.1,5.1],
 [5.1,5.1,5.1,5.1,5.1],
 [5.1,5.1,5.1,5.1,5.1],
 [5.1,5.1,5.1,5.1,5.1],
 [5.1,5.1,5.1,5.1,5.1]]
```


**Implementation/Code:** The following is the code for matrixScale(a,s)
```c++
Matrix matrixScale(Matrix a, double s)
{
    Matrix sol = a;

    for (int i=0;i<a.size();++i)
        for (int j=0;j<a[0].size();j++)
            sol[i][j]*= s;

    return sol;
}
```
**Last Modified:** October/2017
