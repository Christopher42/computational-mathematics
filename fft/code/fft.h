#ifndef FFT_H
#define FFT_H

#include <complex>
#include <valarray>

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;;

void fft(CArray& x);
void fft_optimized(CArray &x);
void ifft(CArray& x);
void ifft_optimized(CArray& x);

#endif