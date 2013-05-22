#include <boost/test/unit_test.hpp>

#include "simrec/image.hpp"
#include <string>

using namespace simrec;

BOOST_AUTO_TEST_SUITE( image_tests )

int sumPixelsInRow(Image image, int width, int rowIndex)
{
    int sum = 0;
    for (int x=0; x<width; x++)
        sum += image.getPixelValue(x, rowIndex);

    return sum;
}

int sumPixelsInColumn(Image image, int height, int columnIndex)
{
    int sum = 0;
    for (int y=0; y<height; y++)
        sum += image.getPixelValue(columnIndex, y);
    
    return sum;
}

BOOST_AUTO_TEST_CASE( open_image ) {
    int width = 241;
    int height = 964;

    int x = 30;
    int y = 300;
    
    std::string filename("./../../misc/sinogram_241x964_8bit.raw");
    
    Image image(filename.c_str(), width, height);

//    int sum = sumPixelsInRow(image, width, 1);
//    BOOST_CHECK_EQUAL(sum, 0);
    BOOST_CHECK_EQUAL(image.getWidth(), width);
    BOOST_CHECK_EQUAL(image.getHeight(), height);
    BOOST_CHECK_EQUAL(image.getSize(), width*height);
    BOOST_CHECK_EQUAL(image.getPixelValue(x,y) != 0, true);
}



BOOST_AUTO_TEST_CASE ( upscale_image) {
    int width = 5;
    int height = 5;

    std::string filename("./../../misc/chess.raw");

    Image image(filename.c_str(), width, height);

    image.upscaleToClosestPowerOfTwo();
    int newWidth = 8;
    int newHeight = 8;

    BOOST_CHECK_EQUAL(sumPixelsInRow(image, newWidth, 0), 0);
    //BOOST_CHECK_EQUAL(sumPixelsInRow(image, newWidth, 6), 0);
    //BOOST_CHECK_EQUAL(sumPixelsInRow(image, newWidth, 7), 0);

    //BOOST_CHECK_EQUAL(sumPixelsInColumn(image, newHeight, 0), 0);
    //BOOST_CHECK_EQUAL(sumPixelsInColumn(image, newHeight, 6), 0);
    //BOOST_CHECK_EQUAL(sumPixelsInColumn(image, newHeight, 7), 0);
}

BOOST_AUTO_TEST_SUITE_END()
