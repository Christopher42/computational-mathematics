**Routine Name:** vectorErrorL1

**Author:** Christopher Johnson

**Language:** C++11. Tested with g++ compiler.

**Declared in** "vectorCode.h"

**Description/Purpose:**
Calculates the l1 norm of the difference between input Vectors.

**Input:**
Vector u and Vector v, typedef of `std::vector<double>`;

**Output:**
A double, indicating the l1 norm of the error between input vectors.

**Usage/Example:**
The user must first define 2 Vectors, after which the method may be called on the vectors.
```C++
Vector a = {1,2,3};
Vector a_bar = {1.1, 1.9, 3.2};
std::cout << "l1 error: " << vectorErrorL1(a,a_bar) << std::endl;
```
Output from the lines above:
```c++
l1 error: 0.4
```


**Implementation/Code:** The following is the code for vectorErrorL1(v)
```c++
double vectorErrorL1 (Vector u, Vector v)
{
    auto err = vectorDiff(u,v);
    return vectorNormL1(err);
}
```

The code for vectorDiff(u,v) is automatically inlined by the compiler, causing it to be inserted into the vector error method without having to call the function at runtime. This increases the running speed, at the cost of a slightly larger executable.
```c++
inline std::vector<double> vectorDiff (Vector u, Vector v)
{
    if (u.size() != v.size())
        return Vector();

    Vector diff (u.size(), 0);
    for(int i=0; i<u.size(); i++)
        diff[i] = v[i]-u[i];
    return diff;
}
```
**Last Modified:** October/2017
