**Routine Name:** fft

**Author:** Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in:** "fft.h"

**Description/Purpose:** Implements fast fourier transform to interpolate given data points with a linear combination of the functions {sin(kx), cos(kx), 1}.

**Input:** `std::valarray<std::complex<double>> Data`. This type is aliased to `CArray` by "fft.h". The number of entries must be a power of 2.

**Output:**
Modifies Data array to contain the solution.

**Usage/Example:**

```C++
#include <iostream>
#include "fft.h"

int main()
{
    const Complex test[] = { 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 };
    CArray data(test, 8);
    CArray data_opt(test, 8);
 
    // forward fft
    fft(data);
 
    std::cout << "fft" << std::endl;
    for (int i = 0; i < 8; ++i)
    {
        std::cout << data[i] << std::endl;
    }
}
```
Output from the lines above:
```c++
fft
(4,0)
(1,-2.41421)
(0,0)
(1,-0.414214)
(0,0)
(1,0.414214)
(0,0)
(1,2.41421)
```


**Implementation/Code:** The following is the code for fft(x).
```c++
// Cooley–Tukey FFT (in-place, divide-and-conquer)
// Higher memory requirements and redundancy although more intuitive
void fft(CArray& x)
{
    const size_t N = x.size();
    if (N <= 1) return;
 
    // divide
    CArray even = x[std::slice(0, N/2, 2)];
    CArray  odd = x[std::slice(1, N/2, 2)];
 
    // conquer
    fft(even);
    fft(odd);
 
    // combine
    for (size_t k = 0; k < N/2; ++k)
    {
        Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        x[k    ] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
}
```
**Last Modified:** December/2017
