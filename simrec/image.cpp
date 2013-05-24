#include "image.hpp"

using namespace simrec;

/// The default constructor
/**
* Reads the image from the given path with the width and height information.
* This class expects the data to be in an 8-bit raw format, with only the
* pixel information in it.
* @param filename the path to the file that is to be read
* @param width the width of the image
* @param height the height of the image
*/
Image::Image(const char* filename, int width, int height)
{
    std::ifstream imageStream(filename, std::ios::in | std::ios::binary | std::ios::ate);

 
    if (imageStream.good())
    {   
        std::ifstream::pos_type size = imageStream.tellg();

        if (size == width*height)
        {       
            char* data = new char[size];
            
            imageStream.seekg(0, std::ios::beg);
            imageStream.read(data, size);
            imageStream.close();
            
            this->imageData = algorithms::initNewComplexArray(size);
            for (int i=0; i<size; i++)
                this->imageData[i] = std::polar(data[i]*1.0, 0.0);

            delete[] data;

            //cout << "Image reading ready!" << endl;
            
            this->width = width;
            this->height = height;
            this->size = size; 
        }
    }
    else
    {
        this->width = -1;
        this->height = -1;
        this->size = -1;
        
        this->imageData = algorithms::initNewComplexArray(1);
    }


}

///Default destructor
Image::~Image()
{
    delete[] this->imageData;
}

int Image::getWidth()
{
    return width;
}

int Image::getHeight()
{
    return height;
}

/**
* @return the size as the number of pixels in the contained image
*/
int Image::getSize()
{
    return size;
}

/**
* @param x the x coordinate value of the pixel
* @param y the y coordinate value of the pixel
* @return the value of the pixel as a real number
*/
int Image::getPixelValue(int x, int y)
{
    if (x >= 0 && y >= 0 && x < width && y < height)
        return std::abs(imageData[y*width + x]);
    else
        return -1;
}

/// Upscales the image
/**
* Upscales the image to a rectangle, which has
* a power-of-two valued side length. The side length
* is determined from the maximum of the width and height of the image,
* so that the resulting side length is the smallest power of two value that is 
* larger than this maximum. The original image data is padded with zeros,
* so that no resizing of the original data happens.
*/
void Image::upscaleToClosestPowerOfTwo()
{
    int newSide = findNewSideLength();

    int newSize = newSide*newSide;

    std::complex<double>* scaledData = algorithms::initNewComplexArray(newSize);
    
    // Calculate the spot where to start adding data
    // so that it gets centered into the new bigger array
    int startX = newSide/2 - getWidth()/2 - 1;
    int startY = newSide/2 - getHeight()/2 - 1;

    copyCurrentDataTo(scaledData, newSide, startX, startY);

    replaceCurrentDataWith(scaledData);

    this->size = newSize;
    this->width = newSide;
    this->height = newSide;
}

std::complex<double>* Image::getData()
{
    return imageData;
}

/**
* Finds the smallest power of two value that is larger than
* the maximum of the width and height of the image
*/
int Image::findNewSideLength()
{
    int longSide = 0;
    if (getWidth() >= getHeight())
        longSide = getWidth();
    else
        longSide = getHeight();

    int newSide = 0;
    for (int i=0; longSide > newSide; i += 1)
        newSide = 1 << i;

    return newSide;
}

/**
* Copies the current data into an array that is larger than the original,
* so that the upper left corner of the original data starts from
* the startX and startY in the new array. A rectangular array is expected,
* so that only the side length of the new array needs to be known.
* @param newArray the array where to copy the original data
* @param newSide the width/height of the new array.
* @param startX the x coordinate value for the starting point for the original data in the new array
* @param startY the y coordinate value for the starting point for the original data in the new array
*/
void Image::copyCurrentDataTo(std::complex<double>* newArray, int newSide, int startX, int startY)
{
    for (int y=0; y<getHeight(); y++)
    {
        for (int x=0; x<getWidth(); x++)
        {
            newArray[(y+startY)*newSide + (x+startX)] = this->imageData[y*getWidth()+x];
        }
    }
}

void Image::replaceCurrentDataWith(std::complex<double>* newData)
{
    delete[] this->imageData;
    
    this->imageData = newData;
}
