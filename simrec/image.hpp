#ifndef SIMREC_IMAGE_HPP
#define SIMREC_IMAGE_HPP

#include <fstream>
#include <iostream>
#include <complex>

namespace simrec {

/* Image reads 8-bit black and white raw image data and 
 * saves it into an array. 
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

    int findNewSideLength();
    void copyCurrentDataTo(std::complex<double>* newArray, int newSide,int startX, int startY);
    std::complex<double>* initNewComplexArray(int size);
    void replaceCurrentDataWith(std::complex<double>* newData);

};

}

#endif
