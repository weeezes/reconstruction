#include "image.hpp"

using namespace simrec;

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
            
            this->imageData = new std::complex<double>[size];
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
        
        this->imageData = new std::complex<double>[1];
    }


}

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

int Image::getSize()
{
    return size;
}

int Image::getPixelValue(int x, int y)
{
    if (x >= 0 && y >= 0 && x < width && y < height)
        return std::abs(imageData[y*width + x]);
    else
        return -1;
}

void Image::upscaleToClosestPowerOfTwo()
{
    int newSide = findNewSideLength();

    int newSize = newSide*newSide;

    std::complex<double>* scaledData = initNewComplexArray(newSize);
    
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

std::complex<double>* Image::initNewComplexArray(int size)
{
    std::complex<double>* complexArray = new std::complex<double>[size];
    for (int i=0; i<size; i++)
    {
        complexArray[i] = std::polar(0.0, 0.0);
    }

    return complexArray;
}

void Image::replaceCurrentDataWith(std::complex<double>* newData)
{
    delete[] this->imageData;
    
    this->imageData = newData;
}
