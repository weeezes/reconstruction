#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <iostream>
#include <complex>

#include "complex_array.hpp"
#include "image.hpp"

namespace simrec {

    namespace utils {
		ComplexArray readFile(const char* filename, const int expectedBytes);
        void saveFile(const char* filename, const ComplexArray& data);

	    void flip2DArray(ComplexArray& data, unsigned int sideLength);

        Image sliceImage(Image image, unsigned int startX, unsigned int startY, unsigned int width, unsigned int height);
        void splitArrayToEvenAndOdd(ComplexArray& toSplit, unsigned int length, ComplexArray& oddResult, ComplexArray& evenResult);
        
        bool isAPowerOfTwo(unsigned int number);

        int round(double v);
        double toRadians(double degrees);
        
        double const PI = 3.14159265;
    }
}

#endif
