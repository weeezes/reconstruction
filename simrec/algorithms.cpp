#include "algorithms.hpp"

using namespace simrec;

void algorithms::fft(std::complex<double>* data, unsigned int length)
{
    if (length == 1)
        return;

    std::complex<double>* even = algorithms::initNewComplexArray(length/2);
    std::complex<double>* odd = algorithms::initNewComplexArray(length/2);

    splitArrayToEvenAndOdd(data, length, odd, even);

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

std::complex<double>* algorithms::initNewComplexArray(unsigned int size)
{
    std::complex<double>* complexArray = new std::complex<double>[size];
    for (int i=0; i<size; i++)
    {
        complexArray[i] = std::polar(0.0, 0.0);
    }

    return complexArray;
}

void algorithms::splitArrayToEvenAndOdd(std::complex<double>* toSplit, unsigned int length, std::complex<double>* oddResult, std::complex<double>* evenResult)
{
    if (!isAPowerOfTwo(length))
        throw "shieet";

    int n = 0;
    for (int i=0; i<length-1; i+=2)
    {
        evenResult[n] = toSplit[i];
        oddResult[n] = toSplit[i+1];
        n++;
    }
}

bool algorithms::isAPowerOfTwo(unsigned int number)
{
    return (number & (number-1)) == 0;
}
