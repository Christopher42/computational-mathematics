**Routine Name:** vectorNormL1

**Author:** Christopher Johnson

**Language:** C++11. Tested with g++ compiler.

**Description/Purpose:**
Calculates the l1 norm of input vector.

**Input:**
Vector v, typedef of std::vector<double>;

**Output:**
A double, indicating the l1 norm of the input value.

**Usage/Example:**
The user must first define a vector, after which the method may be called on the vector.
```C++
    Vector a = {1,2,3};
    std::cout << "Let the vector A be given as\n";
    printVector(a);
    std::cout << "The l1 norm of A is " << vectorNormL1(a) << std::endl;
```
Output from the lines above:
```c++
      The l1 norm of A is 6
```


**Implementation/Code:** The following is the code for vectorNormL1(v)
```c++
      double vectorNormL1 (Vector v)
      {
        double sum = 0.0;
        for (int i=0; i<v.size(); i++)
          sum+=std::abs(v[i]);
        return sum;
      }
```
**Last Modified:** October/2017
