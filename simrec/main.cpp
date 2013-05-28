#include <iostream>
#include <stdlib.h>
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
    
    Image img(filename, x_size, y_size);
    
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
    algorithms::fft2D(img.getData().toArray(), img.getWidth());
    
    std::cout << "Transformed image: " << std::endl;

    for (int y=0; y<img.getHeight(); y++)
    {
        for (int x=0; x<img.getWidth(); x++)
        {
            std::cout << img.getPixelValue(x,y) << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
