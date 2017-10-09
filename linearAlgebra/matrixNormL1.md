**Routine Name:** matrixNormL1

**Author:** Christopher Johnson

**Language:** C++11. Tested with g++ compiler.

**Description/Purpose:** 
Computes the l1 norm of input matrix.

**Input:**
Matrix m, typedef of std::vector<std::vector<double>>.

**Output:**
Returns a double, giving the computed l1 norm of the matrix.

**Usage/Example:**

A Matrix must first be defined, and then the method may be called.
```C++
    Matrix a(5, Vector{-2,-1,0,1,2}); \\Creates a vector with 5 rows of [-2,-1,0,-1,-2]
    std::cout << "The l1 matrix norm of A is " << matrixNormL1(a) << std::endl;
```
Output from the lines above:
```c++
      The l1 matrix norm of A is 10
```


**Implementation/Code:** The following is the code for matrixNormL1(m)
```c++
      double matrixNormL1 (Matrix m)
			{
				double maxColumnSum = 0;
				for (int j=0;j<m[0].size();j++)
				{
					double sum = 0;
					for (int i=0;i<m.size();i++)
						sum+= std::abs(m[i][j]);
					if (sum > maxColumnSum)
						maxColumnSum = sum;
				}
				return maxColumnSum;
			}
```
**Last Modified:** October/2017
