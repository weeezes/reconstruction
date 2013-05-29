#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <iostream>
#include <complex>

#include "complex_array.hpp"

namespace simrec {

    namespace utils {
		ComplexArray readFile(const char* filename, const int expectedBytes);

	    void flip2DArray(std::complex<double>* data, unsigned int sideLength);

        std::complex<double>* initNewComplexArray(unsigned int size);
        
        std::complex<double>* sliceArray(std::complex<double>* array, unsigned int start, unsigned int stop);
        void splitArrayToEvenAndOdd(std::complex<double>* toSplit, unsigned int length, std::complex<double>* oddResult, std::complex<double>* evenResult);
        
        bool isAPowerOfTwo(unsigned int number);

    }
}

#endif