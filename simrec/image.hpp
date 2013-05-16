#ifndef SIMREC_IMAGE_HPP
#define SIMREC_IMAGE_HPP

#include <fstream>
#include <iostream>

namespace simrec {

/* Image reads 8-bit black and white raw image data and 
 * saves it into an array. 
 */
class Image {
public:
    Image(const char* filename, int width, int height);

    int getWidth();
    int getHeight();
    int getSize();
    int getPixelValue(int x, int y);

private:
    char* imageData;
    int width;
    int height;
    int size;
};

}

#endif
