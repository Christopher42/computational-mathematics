**Routine Name:** ifft

**Author:** Rosetta Code (https://rosettacode.org/wiki/Fast_Fourier_transform#C.2B.2B), modified by Christopher Johnson

**Language:** C++. Tested with g++ compiler.

**Declared in:** "fft.h"

**Description/Purpose:** Implements inverse fast fourier transform to restore original data from interpolation with a linear combination of the functions {sin(kx), cos(kx), 1}.

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
 
    // inverse fft
    ifft(data);
 
    std::cout << std::endl << "ifft" << std::endl;
    for (int i = 0; i < 8; ++i)
    {
        std::cout << data[i] << std::endl;
    }
}
```
Output from the lines above:
```c++
ifft
(1,-0)
(1,-5.55112e-17)
(1,2.4895e-17)
(1,-5.55112e-17)
(5.55112e-17,0)
(5.55112e-17,5.55112e-17)
(0,-2.4895e-17)
(5.55112e-17,5.55112e-17)
```


**Implementation/Code:** The following is the code for ifft(x).
```c++
// inverse fft (in-place)
void ifft(CArray& x)
{
    // conjugate the complex numbers
    x = x.apply(std::conj);
 
    // forward fft
    fft( x );
 
    // conjugate the complex numbers again
    x = x.apply(std::conj);
 
    // scale the numbers
    x /= x.size();
}
```
**Last Modified:** December/2017
