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

    img.upscaleToClosestPowerOfTwo();

    std::complex<double>* data = img.getData().toArray();

    algorithms::fft2D(data, img.getWidth());

    algorithms::ifft2D(data, img.getWidth());
    
    ComplexArray d(data, img.getWidth()*img.getWidth());
    Image filtered(d, img.getWidth(), img.getHeight());

    int sx = (img.getWidth()-x_size)/2;
    int sy = (img.getHeight()-y_size)/2;
    Image slice = utils::sliceImage(filtered, sx, sy, x_size, y_size);

   // Image transformed = algorithms::inverse_radon(slice, 0, 20, 10);
    Image transformed = slice;
    std::cout << "Width: " << transformed.getWidth() << std::endl << "Height: " << transformed.getHeight() << std::endl;
    std::cout << "Data points: " << transformed.getData().getSize() << std::endl; 
    utils::saveFile("transformed.raw", transformed.getData());

    return 0;
}
