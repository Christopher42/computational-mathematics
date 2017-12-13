**Routine Name:** ifft_optimized

**Author:** Rosetta Code (https://rosettacode.org/wiki/Fast_Fourier_transform#C.2B.2B), modified by Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in:** "fft.h"

**Description/Purpose:** Implements inverse fast fourier transform to restore original data from interpolation with a linear combination of the functions {sin(kx), cos(kx), 1}. Optimized version.

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
 
    // opt forward fft
    fft_optimized(data);

    // opt inverse fft
    ifft_optimized(data);
 
    std::cout << std::endl << "optimized ifft" << std::endl;
    for (int i = 0; i < 8; ++i)
    {
        std::cout << data[i] << std::endl;
    }
    return 0;
}
```
Output from the lines above:
```c++
optimized ifft
(1,-2.77556e-17)
(1,-8.32667e-17)
(1,-0)
(1,-2.77556e-17)
(0,2.77556e-17)
(0,8.32667e-17)
(0,-0)
(1.11022e-16,2.77556e-17)
```


**Implementation/Code:** The following is the code for ifft_optimized(x).
```c++
// inverse fft (in-place) - using optimized Cooley-Tukey FFT
void ifft_optimized(CArray& x)
{
    // conjugate the complex numbers
    x = x.apply(std::conj);
 
    // forward fft
    fft_optimized( x );
 
    // conjugate the complex numbers again
    x = x.apply(std::conj);
 
    // scale the numbers
    x /= x.size();
}
```
**Last Modified:** December/2017
