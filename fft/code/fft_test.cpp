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
 
    // inverse fft
    ifft(data);
 
    std::cout << std::endl << "ifft" << std::endl;
    for (int i = 0; i < 8; ++i)
    {
        std::cout << data[i] << std::endl;
    }

    // opt forward fft
    fft_optimized(data);
 
    std::cout << std::endl << "optmimized fft" << std::endl;
    for (int i = 0; i < 8; ++i)
    {
        std::cout << data[i] << std::endl;
    }
 
    // opt inverse fft
    ifft_optimized(data);
 
    std::cout << std::endl << "optimized ifft" << std::endl;
    for (int i = 0; i < 8; ++i)
    {
        std::cout << data[i] << std::endl;
    }
    return 0;
}