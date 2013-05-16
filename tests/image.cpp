#include <boost/test/unit_test.hpp>

#include "simrec/image.hpp"
#include <string>

using namespace simrec;

BOOST_AUTO_TEST_SUITE( image_tests )

BOOST_AUTO_TEST_CASE( open_image ) {
    int width = 241;
    int height = 964;

    int x = 30;
    int y = 300;
    
    std::string filename("./../../misc/sinogram_241x964_8bit.raw");
    
    Image image(filename.c_str(), width, height);

    BOOST_CHECK_EQUAL(image.getWidth(), width);
    BOOST_CHECK_EQUAL(image.getHeight(), height);
    BOOST_CHECK_EQUAL(image.getSize(), width*height);
    BOOST_CHECK_EQUAL(image.getPixelValue(x,y) != 0, true);
}

BOOST_AUTO_TEST_SUITE_END()
