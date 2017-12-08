**Routine Name:** matrixVectorProduct

**Author:** Christopher Johnson

**Language:** C++11. Tested with g++ compiler.

**Declared in** "matrix.h"

**Description/Purpose:** 
Multiplies Matrix by Vector.

**Input:**
Matrix a and Vector v, where Matrix is a typedef of `std::vector<std::vector<double>>` and Vector is a typedef of `std::vector<double>`.

**Output:**
Returns a Vector, typedef of `std::vector<double>`. The size is equal to rows(a).

**Usage/Example:**

A Matrix must first be defined, and then the method may be called.
```C++
Matrix b(5, Vector(5,1)); \\5*5 matrix of all ones
b = matrixAdd(b,identityMatrix(5));
Vector v{1,2,3,4,5};
std::cout << "B * v is\n"
printVector(matrixVectorProduct(b,v));
```
Output from the lines above:
```c++
B * v is
[16, 17, 18, 19, 20]
```


**Implementation/Code:** The following is the code for matrixVectorProduct(a,v)
```c++
Vector matrixVectorProduct(Matrix a, Vector v)
{
    int m = a.size();
    int n = a[0].size();
    Vector sol(m,0);

    for (int i=0;i<m;++i)
        for (int j=0;j<n;++j)
            sol[i]+=a[i][j]*v[j];
    return sol;
}
```
**Last Modified:** October/2017
