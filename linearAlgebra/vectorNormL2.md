**Routine Name:** vectorNormL2

**Author:** Christopher Johnson

**Language:** C++11. Tested with g++ compiler.

**Declared in** "vectorCode.h"

**Description/Purpose:**
Calculates the l2 norm of input vector.

**Input:**
Vector v, typedef of `std::vector<double>`;

**Output:**
A double, indicating the l2 norm of the input value.

**Usage/Example:**
The user must first define a vector, after which the method may be called on the vector.
```C++
Vector a = {1,2,3};
std::cout << "Let the vector A be given as\n";
printVector(a);
std::cout << "The l2 norm of A is " << vectorNormL1(a) << std::endl;
```
Output from the lines above:
```c++
The l2 norm of A is 3.74166
```


**Implementation/Code:** The following is the code for vectorNormL2(v)
```c++
double vectorNormL2 (Vector v)
{
    double sum_of_squares = 0.0;
    for (int i=0; i<v.size(); i++)
        sum_of_squares+=v[i]*v[i];
    return sqrt(sum_of_squares);
}
```
**Last Modified:** October/2017
