**Routine Name:**

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in** "parallelOperations.h"

**Description/Purpose:** 
Performs Matrix-Matrix multiplication utilizing openmp package for increased performance.

**Input:**
Matrices a and b, both passed by reference.

**Output:**
Returns a new matrix, containing the output from operation.

**Usage/Example:**

<explain conditions of usage>
```C++
	#include "parallelOperation.h"
	#include "matrix.h"

	int main (void)
	{
		int n=3;
	    Matrix A(n,Vector(n,0)); //init n*n matrix of zeroes
	    Matrix B(n,Vector(n,0));

	    Matrix C = parallelMatrixMatrixProduct(A,B);
	}
```
Output from the lines above:
```c++
	
```
<explain output>


**Implementation/Code:** The following is the code for <function name>
```c++
      
```
**Last Modified:** October/2017
