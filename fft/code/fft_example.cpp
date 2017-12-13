#include <iostream>
#include "fft.h"

const double PI = 3.141592653589793238460;

double f (double x)
{
    return (x<PI)?(x):(2*PI-x);
}

int main()
{
    double tol = pow(10.0,-10.0);
    int n = 3;
    int size[n] = {32,64,128};
    for (int i=0;i<n;++i)
    {
        int s = size[i];
        CArray data(s);
        for (int j=0;j<s;++j)
        {
            double x = 2 * PI * j / s;
            data[j] = Complex(f(x));
        }
        std::cout << std::endl << "using " << s << " interpolation points";

        // opt forward fft
        fft_optimized(data);
     
        std::cout << std::endl << "optmimized fft" << std::endl;
        for (int i = 0; i < s; ++i)
        {
            std::cout << data[i] << std::endl;
        }
     
        // opt inverse fft
        ifft_optimized(data);
     
        std::cout << std::endl << "optimized ifft" << std::endl;
        for (int i = 0; i < s; ++i)
        {
            if (data[i].imag() < tol)
                data[i] = data[i].real();
            std::cout << data[i] << std::endl;
        }
    }
    return 0;
}