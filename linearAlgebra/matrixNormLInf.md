**Routine Name:** matrixNormLInf

**Author:** Christopher Johnson

**Language:** C++11. Tested with g++ compiler.

**Description/Purpose:** 
Computes the l-infinity norm of input matrix.

**Input:**
Matrix m, typedef of `std::vector<std::vector<double>>`.

**Output:**
Returns a double, giving the computed l-infinity norm of the matrix.

**Usage/Example:**

A Matrix must first be defined, and then the method may be called.
```C++
    Matrix a(5, Vector{-2,-1,0,1,2}); \\Creates a vector with 5 rows of [-2,-1,0,-1,-2]
    std::cout << "The l-infinity matrix norm of A is " << matrixNormLInf(a) << std::endl;
```
Output from the lines above:
```c++
      The l-infinity matrix norm of A is 6
```


**Implementation/Code:** The following is the code for matrixNormLInf(m)
```c++
			double matrixNormLInf (Matrix m)
			{
				double maxRowSum = 0;
				for (int i=0;i<m.size();i++)
				{
					double sum = 0;
					for (int j=0;j<m[0].size();j++)
						sum+= std::abs(m[i][j]);
					if (sum > maxRowSum)
						maxRowSum = sum;
				}
				return maxRowSum;
			}
```
**Last Modified:** October/2017
