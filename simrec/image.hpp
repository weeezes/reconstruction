#ifndef SIMREC_IMAGE_HPP
#define SIMREC_IMAGE_HPP

#include <fstream>
#include <iostream>
#include <complex>

#include "algorithms.hpp"

namespace simrec {

///Image reads and contains 8-bit black and white image data.

/**
* The Image class is used for reading 8-bit image data from a file and to
* keep track of it's information, mainly the width and height of the image.
*/

class Image {
public:
    Image(const char* filename, int width, int height);
    ~Image();

    int getWidth();
    int getHeight();
    int getSize();
    int getPixelValue(int x, int y);
    
    void upscaleToClosestPowerOfTwo();
    std::complex<double>* getData();

private:
    std::complex<double>* imageData;
    int width;
    int height;
    int size;

    // deny copying of the object
    Image(const Image& other);

    int findNewSideLength();
    void copyCurrentDataTo(std::complex<double>* newArray, int newSide,int startX, int startY);
    void replaceCurrentDataWith(std::complex<double>* newData);

};

}

#endif
