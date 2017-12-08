**Routine Name:** matrixMatrixProduct

**Author:** Christopher Johnson

**Language:** C++11. Tested with g++ compiler.

**Description/Purpose:** 
Performs Matrix-Matrix multiplication.

**Input:**
Matrix a and Matrix b, where Matrix is a typedef of `std::vector<std::vector<double>>`.

**Output:**
Returns a Matrix, typedef of `std::vector<std::vector<double>>`. The size is equal rows(a) x cols(b).

**Usage/Example:**

Two Matrices must first be defined, and then the method may be called.
```C++
    Matrix c = { {1,2,3},{4,5,6} };
    Matrix d = { {7,8},{9,10},{11,12} };
    std::cout << "C * D is\n"
    printVector(matrixMatrixProduct(c,d));
```
Output from the lines above:
```c++
    C * D is
    [[58,64],
    [139,154]]
```


**Implementation/Code:** The following is the code for matrixMatrixProduct(a,b)
```c++
    Matrix matrixMatrixProduct(Matrix a, Matrix b)
    {
        int n = a.size();
	int m = b.size();
	int r = b[0].size();

        Matrix sol(n, Vector(r,0));

        for(int i=0;i<n;++i)
	    for(int j=0;j<r;++j)
	        for(int k=0;k<m;++k)
		    sol[i][j]+=a[i][k]*b[k][j];
        return sol;
    }
```
**Last Modified:** October/2017
