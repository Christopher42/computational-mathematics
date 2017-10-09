**Routine Name:** vectorNormLInf

**Author:** Christopher Johnson

**Language:** C++11. Tested with g++ compiler.

**Description/Purpose:**
Calculate the l-infinity norm of input vector.

**Input:**
Vector v, typedef of `std::vector<double>`;

**Output:**
A double, indicating the l-infinity norm of the input value.

**Usage/Example:**
The user must first define a vector, after which the method may be called on the vector.
```C++
    Vector a = {1,2,3};
    std::cout << "Let the vector A be given as\n";
    printVector(a);
    std::cout << "The l-infinity norm of A is " << vectorNormL1(a) << std::endl;
```
Output from the lines above:
```c++
      The l-infinity norm of A is 3
```


**Implementation/Code:** The following is the code for vectorNormLInf(v)
```c++
      double vectorNormL1 (Vector v)
      {
          double maxElement = v[0];
          for(int i=1; i<v.size(); i++)
            if (v[i]>maxElement)
              maxElement=v[i];
          return maxElement;
      }
```
**Last Modified:** October/2017
