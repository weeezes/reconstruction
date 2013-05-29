#include "algorithms.hpp"

using namespace simrec;

/// Fast Fourier Transform, based on the Cooley-Tukey algorithm
/**
* Calculates the Fourier transform of the input data in place.
* @param data input data to transform
* @param length length of the data, must be a value that is a power of two.
*/
void algorithms::fft(std::complex<double>* data, unsigned int length)
{
    if (length == 1)
        return;

    if (!utils::isAPowerOfTwo(length))
        throw "Not a power of two!";

    std::complex<double>* even = utils::initNewComplexArray(length/2);
    std::complex<double>* odd = utils::initNewComplexArray(length/2);

    utils::splitArrayToEvenAndOdd(data, length, odd, even);

    algorithms::fft(even, length/2);
    algorithms::fft(odd, length/2);

    for (int k=0; k<=length/2-1; k++)
    {
        data[k] = even[k] + odd[k]*std::polar(1.0, -2*3.14*k/length);
        data[k+length/2] = even[k] - odd[k]*std::polar(1.0, -2*3.14*k/length);
    }
    
    delete[] even;
    delete[] odd;
}

/// Fast Fourier Transform in two dimensions, based on the Cooley-Tukey algorithm
/**
* Calculates the Fourier transform of the 2d input data in place.
* @param data the input data to transform
* @param sideLength the sides length of the rectangular data. Must be a value that
* is a power of two
*/
void algorithms::fft2D(std::complex<double>* data, unsigned int sideLength)
{
    if (!utils::isAPowerOfTwo(sideLength))
        throw "Not a power of two!";

    utils::flip2DArray(data, sideLength);

    for (int y=0; y<sideLength; y++)
    { 
        algorithms::fft(&data[y*sideLength], sideLength);
    }

    utils::flip2DArray(data, sideLength);
}

/// Inverse Fast Fourier Transform, based on the Cooley-Tukey algorithm
/**
* Calculates the Inverse Fourier transform of the input data in place.
* @param data input data to transform
* @param length length of the data, must be a value that is a power of two.
*/
void algorithms::ifft(std::complex<double>* data, unsigned int length)
{
    if (length == 1)
        return;

    if (!utils::isAPowerOfTwo(length))
        throw "Not a power of two!";

    std::complex<double>* even = utils::initNewComplexArray(length/2);
    std::complex<double>* odd = utils::initNewComplexArray(length/2);

    utils::splitArrayToEvenAndOdd(data, length, odd, even);

    algorithms::ifft(even, length/2);
    algorithms::ifft(odd, length/2);

    for (int k=0; k<=length/2-1; k++)
    {
        data[k] = even[k] + odd[k]*std::polar(1.0, 2*3.14*k/length);
        data[k+length/2] = even[k] - odd[k]*std::polar(1.0, 2*3.14*k/length);
    }
    
    delete[] even;
    delete[] odd;
}

/// Inverse Fast Fourier Transform in two dimensions, based on the Cooley-Tukey algorithm
/**
* Calculates the Inverse Fourier transform of the 2d input data in place.
* @param data the input data to transform
* @param sideLength the sides length of the rectangular data. Must be a value that
* is a power of two
*/
void algorithms::ifft2D(std::complex<double>* data, unsigned int sideLength)
{
    if (!utils::isAPowerOfTwo(sideLength))
        throw "Not a power of two!";

    utils::flip2DArray(data, sideLength);

    for (int y=0; y<sideLength; y++)
    { 
        algorithms::ifft(&data[y*sideLength], sideLength);
    }

    utils::flip2DArray(data, sideLength);

	for (int i=0; i<sideLength*sideLength; i++)
		data[i] = data[i]/std::complex<double>(8.0, 0.0);

}
