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

    for (int y=0; y<sideLength; y++)
    { 
        algorithms::fft(&data[y*sideLength], sideLength);
    }

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

        // normalization
        for (int i=y*sideLength; i<y*sideLength+sideLength; i++)
            data[i] = data[i]/std::complex<double>(sideLength, 0.0);
    }
        

    utils::flip2DArray(data, sideLength);

    for (int y=0; y<sideLength; y++)
    { 
        algorithms::ifft(&data[y*sideLength], sideLength);

        // normalization
        for (int i=y*sideLength; i<y*sideLength+sideLength; i++)
            data[i] = data[i]/std::complex<double>(sideLength, 0.0);
    }
}

Image algorithms::inverse_radon(Image input, float angleStart, float angleStop, float angleStep)
{
    // estimate output width
    int outputWidth = 2*std::floor(input.getWidth()/(2*std::sqrt(2)));

    ComplexArray transformedData(outputWidth*outputWidth);
    ComplexArray inputData = input.getData();

    int midIndex = (int) (input.getHeight()/2 + 0.5);
    for (int y=0; y<outputWidth; y++)
    {
        for (int x=0; x<outputWidth; x++)
        {
            for (int k=angleStart; k<angleStop; k+=angleStep)
            {
                int t = (int)(x*std::sin(k) + y*std::cos(k));
                if (t > 0 && t < input.getHeight())
                    transformedData[y*outputWidth+x] += inputData[k+ t*input.getWidth()];
            }
        }
    }

    Image transformed(transformedData, outputWidth, outputWidth);

    return transformed;
}
