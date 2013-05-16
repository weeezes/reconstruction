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
            this->imageData = new char[size];
            
            imageStream.seekg(0, std::ios::beg);
            imageStream.read(this->imageData, size);            imageStream.close();
    
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
        
        this->imageData = new char[1];
    }


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
        return imageData[y*width + x];
    else
        return -1;
}
