**Routine Name:** dotProduct

**Author:** Christopher Johnson

**Language:** C++11. Tested with g++ compiler.

**Declared in** "vectorCode.h"

**Description/Purpose:**
Calculates the dot product of input Vectors.

**Input:**
Vector u and Vector v, typedef of `std::vector<double>`;

**Output:**
A double, indicating the dot product of input vectors.

**Usage/Example:**
The user must first define 2 Vectors, after which the method may be called on the vectors.
```C++
Vector a = {1,2,3};
Vector a_bar = {1.1, 1.9, 3.2};
std::cout << "The dot product of A and A* is " << dotProduct(a,a_bar) << std::endl;
```
Output from the lines above:
```c++
The dot product of A and A* is 14.5
```


**Implementation/Code:** The following is the code for dotProduct(u,v)
```c++
double dotProduct (Vector u, Vector v)
{
double sum = 0;
for (int i=0;i<u.size();++i)
    sum += u[i]*v[i];
return sum;
}
```

**Last Modified:** October/2017
