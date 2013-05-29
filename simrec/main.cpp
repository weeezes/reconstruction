#include <iostream>
#include <stdlib.h>

#include <complex>

#include "utils.hpp"
#include "image.hpp"
#include "algorithms.hpp"

using namespace simrec;

int main(int argc, char* argv[]) {
    if (argc < 4) 
    {
        std::cout << "need arguments: file_name x_size y_size" << std::endl;
        return 1;
    }
    
    const char* filename = argv[1];
    int x_size = atoi(argv[2]);
    int y_size = atoi(argv[3]);
    
    Image img(utils::readFile(filename, x_size*y_size), x_size, y_size);
    
    std::cout << "Image: " << std::endl;

    for (int y=0; y<img.getHeight(); y++)
    {
        for (int x=0; x<img.getWidth(); x++)
        {
            std::cout << img.getPixelValue(x,y) << " ";
        }
        std::cout << std::endl;
    }
 
    img.upscaleToClosestPowerOfTwo();

    std::complex<double>* data = img.getData().toArray();

    algorithms::fft2D(data, img.getWidth());
    
    std::cout << "Transformed image: " << std::endl;

    for (int y=0; y<img.getHeight(); y++)
    {
        for (int x=0; x<img.getWidth(); x++)
        {
            std::cout << std::abs(data[y*img.getWidth()+x]) << " ";
        }
        std::cout << std::endl;
    }

    algorithms::ifft2D(data, img.getWidth());
    
    std::cout << "Inverse transformed image: " << std::endl;

    for (int y=0; y<img.getHeight(); y++)
    {
        for (int x=0; x<img.getWidth(); x++)
        {
            std::cout << std::abs(data[y*img.getWidth()+x]) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
