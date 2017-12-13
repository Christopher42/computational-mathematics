**Routine Name:** fft_optimized

**Author:** Rosetta Code (https://rosettacode.org/wiki/Fast_Fourier_transform#C.2B.2B), modified by Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in:** "fft.h"

**Description/Purpose:** Implements fast fourier transform to interpolate given data points with a linear combination of the functions {sin(kx), cos(kx), 1}. Optimized version.

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
 
    std::cout << std::endl << "optmimized fft" << std::endl;
    for (int i = 0; i < 8; ++i)
    {
        std::cout << data[i] << std::endl;
    }
}
```
Output from the lines above:
```c++
optmimized fft
(4,0)
(1,-2.41421)
(0,0)
(1,-0.414214)
(0,0)
(1,0.414214)
(0,0)
(1,2.41421)
```


**Implementation/Code:** The following is the code for fft_optimized(x).
```c++
// Cooley-Tukey FFT (in-place, breadth-first, decimation-in-frequency)
// Better optimized but less intuitive
// !!! Warning : in some cases this code make result different from not optimased version above (need to fix bug)
// The bug is now fixed @2017/05/30 
void fft_optimized(CArray &x)
{
    // DFT
    unsigned int N = x.size(), k = N, n;
    double thetaT = 3.14159265358979323846264338328L / N;
    Complex phiT = Complex(cos(thetaT), -sin(thetaT)), T;
    while (k > 1)
    {
        n = k;
        k >>= 1;
        phiT = phiT * phiT;
        T = 1.0L;
        for (unsigned int l = 0; l < k; l++)
        {
            for (unsigned int a = l; a < N; a += n)
            {
                unsigned int b = a + k;
                Complex t = x[a] - x[b];
                x[a] += x[b];
                x[b] = t * T;
            }
            T *= phiT;
        }
    }
    // Decimate
    unsigned int m = (unsigned int)log2(N);
    for (unsigned int a = 0; a < N; a++)
    {
        unsigned int b = a;
        // Reverse bits
        b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
        b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
        b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
        b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
        b = ((b >> 16) | (b << 16)) >> (32 - m);
        if (b > a)
        {
            Complex t = x[a];
            x[a] = x[b];
            x[b] = t;
        }
    }
    //// Normalize (This section make it not working correctly)
    //Complex f = 1.0 / sqrt(N);
    //for (unsigned int i = 0; i < N; i++)
    //  x[i] *= f;
}
```
**Last Modified:** December/2017
