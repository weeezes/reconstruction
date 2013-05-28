#include "utils.hpp"

using namespace simrec;

std::complex<double>* utils::sliceArray(std::complex<double>* array, unsigned int start, unsigned int stop)
{
    if (stop <= start)
        throw "Stop can't be lower than start";

    std::complex<double>* slice = utils::initNewComplexArray(stop-start);
    for (int i=start, k=0; i<stop; i++, k++)
        slice[k] = array[i];

    return slice;
}

/// Transposes the given array
/**
* @param data the 2D array for transposing
* @param sideLength the side length for the rectangular data, has to be a value that is a power of two
*/
void utils::flip2DArray(std::complex<double>* data, unsigned int sideLength)
{
	if (!isAPowerOfTwo(sideLength))
		throw "Not a power of two!";

	for (int y=0; y<sideLength; y++)
	{
		for (int x=y; x<sideLength; x++)
		{
			std::complex<double> tmp = data[y*sideLength+x];
			data[y*sideLength+x] = data[x*sideLength+y];
			data[x*sideLength+y] = tmp;
		}
	}
}

std::complex<double>* utils::initNewComplexArray(unsigned int size)
{
    std::complex<double>* complexArray = new std::complex<double>[size];
    for (int i=0; i<size; i++)
    {
        complexArray[i] = std::polar(0.0, 0.0);
    }

    return complexArray;
}

/// Splits an array by even and odd indices
/**
* @param toSplit the array that gets split.
* @param length the length of the array, the value is expected to be a power of two.
* @param oddResult an array with a size of length/2, where the odd index values are saved to
* @param evenResult an array with a size of length/2, where the even index values are saved to
*/
void utils::splitArrayToEvenAndOdd(std::complex<double>* toSplit, unsigned int length, std::complex<double>* oddResult, std::complex<double>* evenResult)
{
    if (!isAPowerOfTwo(length))
        throw "Not a power of two!";

    int n = 0;
    for (int i=0; i<length-1; i+=2)
    {
        evenResult[n] = toSplit[i];
        oddResult[n] = toSplit[i+1];
        n++;
    }
}

/**
* Checks if the input number is a power of two value
*/
bool utils::isAPowerOfTwo(unsigned int number)
{
    // true case: 100 & ( 100 - 1 ) -> 100 & 011 = 0 == 0
    // false case: 011 & ( 011 - 1 ) -> 011 & 010 = 010 != 0
    return (number & (number-1)) == 0;
}
