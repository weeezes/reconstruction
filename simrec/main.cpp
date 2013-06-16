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

    img.upscaleToClosestPowerOfTwo();

    ComplexArray data = img.getData();

	//Filter the data and ifft it back
    algorithms::fft2D(data, img.getWidth());
    algorithms::lowPassFilter(data, img.getWidth(), img.getHeight(), 0.8);
	algorithms::rampFilter(data, img.getWidth(), img.getHeight(), 30.0);
    algorithms::ifft2D(data, img.getWidth());


    Image filtered(data, img.getWidth(), img.getHeight());
   

	int sx = (img.getWidth()-x_size)/2.0;
	int sy = (img.getHeight()-y_size)/2.0;
	Image slice = utils::sliceImage(filtered, sx, sy, x_size, y_size);

    std::cout << "./filtered.raw: " << std::endl;
    std::cout << "\tWidth: " << slice.getWidth() << std::endl;
    std::cout << "\tHeight: " << slice.getHeight() << std::endl;
    std::cout << "\tData points: " << slice.getData().getSize() << std::endl;
    std::cout << std::endl; 
    utils::saveFile("filtered.raw", slice.getData());

    Image transformed = algorithms::inverseRadonTransform(slice, 0, 180, 1);

    std::cout << "./transformed.raw " << std::endl;
    std::cout << "\tWidth: " << transformed.getWidth() << std::endl; 
    std::cout << "\tHeight: " << transformed.getHeight() << std::endl;
    std::cout << "\tData points: " << transformed.getData().getSize() << std::endl;
    std::cout << std::endl; 
    utils::saveFile("transformed.raw", transformed.getData());

    return 0;
}
