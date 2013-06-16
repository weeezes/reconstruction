#include <boost/test/unit_test.hpp>

#include "simrec/utils.hpp"
#include "simrec/image.hpp"

#include <string>

using namespace simrec;

BOOST_AUTO_TEST_SUITE( image_tests )

int sumPixelsInRow(Image &image, int width, int rowIndex)
{
    int sum = 0;
    for (int x=0; x<width; x++)
        sum += image.getPixelValue(x, rowIndex);

    return sum;
}

int sumPixelsInColumn(Image &image, int height, int columnIndex)
{
    int sum = 0;
    for (int y=0; y<height; y++)
        sum += image.getPixelValue(columnIndex, y);
    
    return sum;
}

BOOST_AUTO_TEST_CASE ( upscale_image) {
    int width = 5;
    int height = 5;

    std::string filename("./../../misc/chess.raw");

    Image image(utils::readFile(filename.c_str(), width*height), width, height);

    image.upscaleToClosestPowerOfTwo();
    int newWidth = 8;
    int newHeight = 8;

    int sum = 0;
    for (int y=0; y<newHeight; y++)
        sum += image.getPixelValue(0, y);

    BOOST_CHECK_EQUAL(sumPixelsInRow(image, newWidth, 0), 0);
    BOOST_CHECK_EQUAL(sumPixelsInRow(image, newWidth, 6), 0);
    BOOST_CHECK_EQUAL(sumPixelsInRow(image, newWidth, 7), 0);

    BOOST_CHECK_EQUAL(sumPixelsInColumn(image, newHeight, 0), 0);
    BOOST_CHECK_EQUAL(sumPixelsInColumn(image, newHeight, 6), 0);
    BOOST_CHECK_EQUAL(sumPixelsInColumn(image, newHeight, 7), 0);

    BOOST_CHECK_EQUAL(image.getPixelValue(2, 1), 255); 
    BOOST_CHECK_EQUAL(image.getPixelValue(4, 1), 255);

    BOOST_CHECK_EQUAL(image.getPixelValue(1, 2), 255);
    BOOST_CHECK_EQUAL(image.getPixelValue(3, 2), 255);
    BOOST_CHECK_EQUAL(image.getPixelValue(5, 2), 255);

    BOOST_CHECK_EQUAL(image.getPixelValue(2, 3), 255);
    BOOST_CHECK_EQUAL(image.getPixelValue(4, 3), 255);

    BOOST_CHECK_EQUAL(image.getPixelValue(1, 4), 255);
    BOOST_CHECK_EQUAL(image.getPixelValue(3, 4), 255);
    BOOST_CHECK_EQUAL(image.getPixelValue(5, 4), 255);

    BOOST_CHECK_EQUAL(image.getPixelValue(2, 5), 255);
    BOOST_CHECK_EQUAL(image.getPixelValue(4, 5), 255);
}

BOOST_AUTO_TEST_SUITE_END()
