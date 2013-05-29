#include <boost/test/unit_test.hpp>

#include <complex>
#include <iostream>
#include "simrec/utils.hpp"

using namespace simrec;

BOOST_AUTO_TEST_SUITE( utils_test )

BOOST_AUTO_TEST_CASE( read_file ) {
    int width = 241;
    int height = 964;

    int x = 30;
    int y = 300;
    
    std::string filename("./../../misc/sinogram_241x964_8bit.raw");
    
    ComplexArray file = utils::readFile(filename.c_str(), width*height);

    BOOST_CHECK_EQUAL( file.getSize(), width*height );
	
    BOOST_CHECK( file[y*width+x] != std::complex<double>(0.0, 0.0) );
}

BOOST_AUTO_TEST_CASE( init_complex_array )
{
    int size = 4;
    std::complex<double>* array = utils::initNewComplexArray(size);
    for (int i=0; i<size; i++)
    {
        BOOST_CHECK_EQUAL(array[i], std::polar(0.0, 0.0));
    }

    delete[] array;
}

BOOST_AUTO_TEST_CASE( split_complex_array )
{
    int size = 4;
    std::complex<double>* array = utils::initNewComplexArray(size);
    for (int i=0; i<size; i++)
    {
        array[i] = std::polar(i*1.0, 0.0);
    }

    std::complex<double>* even = utils::initNewComplexArray(2);
    std::complex<double>* odd = utils::initNewComplexArray(2);

    utils::splitArrayToEvenAndOdd(array, size, odd, even);

    BOOST_CHECK_EQUAL(even[0], std::polar(0.0, 0.0));
    BOOST_CHECK_EQUAL(even[1], std::polar(2.0, 0.0));
    BOOST_CHECK_EQUAL(odd[0], std::polar(1.0, 0.0));
    BOOST_CHECK_EQUAL(odd[1], std::polar(3.0, 0.0));
    
    delete[] array;
    delete[] even;
    delete[] odd;
}

BOOST_AUTO_TEST_CASE( flip_complex_array )
{
	int sideLength = 8;
    std::complex<double>* array = utils::initNewComplexArray(sideLength*sideLength);
    
    for (int i=0; i<sideLength*sideLength; i++)
        array[i] = std::complex<double>(i*1.0, 0.0);

    
	utils::flip2DArray(array, sideLength);

//    for (int y=0; y<sideLength; y++)
//    {
//        for (int x=0; x<sideLength; x++)
//            std::cout << array[y*sideLength + x] << " ";
//        std::cout << std::endl;
//    }

	BOOST_CHECK_EQUAL(array[0], std::complex<double>(0.0, 0.0));
    BOOST_CHECK_EQUAL(array[7], std::complex<double>(56.0,0.0));
    BOOST_CHECK_EQUAL(array[56], std::complex<double>(7.0, 0.0));
    BOOST_CHECK_EQUAL(array[sideLength*sideLength-1], std::complex<double>(63.0, 0.0));

    utils::flip2DArray(array, sideLength);

    BOOST_CHECK_EQUAL(array[0], std::complex<double>(0.0, 0.0));
    BOOST_CHECK_EQUAL(array[7], std::complex<double>(7.0, 0.0));
    BOOST_CHECK_EQUAL(array[56], std::complex<double>(56.0, 0.0));
    BOOST_CHECK_EQUAL(array[sideLength*sideLength-1], std::complex<double>(63.0, 0.0));

    delete[] array;
}

BOOST_AUTO_TEST_SUITE_END()
