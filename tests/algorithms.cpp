#include <boost/test/unit_test.hpp>

#include <complex>
#include <iostream>

#include "simrec/utils.hpp"
#include "simrec/algorithms.hpp"

using namespace simrec;

BOOST_AUTO_TEST_SUITE( algorithm_test )

BOOST_AUTO_TEST_CASE( one_dimensional_fft_1 )
{
    int size = 4;
    std::complex<double>* data = utils::initNewComplexArray(size);
    for (int i=0; i<size; i++)
        data[i] = std::polar(1.0, 0.0);

    algorithms::fft(data, size);

    BOOST_CHECK_EQUAL(data[0], std::polar(4.0, 0.0));
    BOOST_CHECK_EQUAL(data[1], std::polar(0.0, 0.0));
    BOOST_CHECK_EQUAL(data[2], std::polar(0.0, 0.0));
    BOOST_CHECK_EQUAL(data[3], std::polar(0.0, 0.0));

    delete[] data;
}

BOOST_AUTO_TEST_CASE( one_dimensional_fft_2 )
{
    int size = 4;
    std::complex<double>* data = utils::initNewComplexArray(size);

    data[0] = std::polar(1.0, 0.0);
    data[1] = std::polar(0.0, 0.0);
    data[2] = std::polar(0.0, 0.0);
    data[3] = std::polar(1.0, 0.0);

    algorithms::fft(data, size);

    double epsilon = 0.001;
    BOOST_CHECK_EQUAL(data[0], std::polar(2.0, 0.0));
    BOOST_CHECK( std::abs(std::real(data[1]) - 1.0) < epsilon);
    BOOST_CHECK( std::abs(std::imag(data[1]) - 1.0) < epsilon);
    BOOST_CHECK_EQUAL(data[2], std::polar(0.0, 0.0));
    BOOST_CHECK( std::abs(std::real(data[3]) - 1.0) < epsilon);
    BOOST_CHECK( std::abs(std::imag(data[3]) + 1.0) < epsilon);

    delete[] data;
}

BOOST_AUTO_TEST_CASE( two_dimensional_fft_1 )
{
    int sideLength = 2;
    std::complex<double>* data = utils::initNewComplexArray(sideLength*sideLength);
    for (int i=0; i<sideLength*sideLength; i++)
        data[i] = std::polar(1.0, 0.0);

    algorithms::fft2D(data, sideLength);

    BOOST_CHECK_EQUAL(data[0], std::polar(2.0, 0.0));
    BOOST_CHECK_EQUAL(data[1], std::polar(2.0, 0.0));
    BOOST_CHECK_EQUAL(data[2], std::polar(0.0, 0.0));
    BOOST_CHECK_EQUAL(data[3], std::polar(0.0, 0.0));

    delete[] data;
}

BOOST_AUTO_TEST_CASE( two_dimensional_fft_2 )
{
    int sideLength = 4;
    std::complex<double>* data = utils::initNewComplexArray(sideLength*sideLength);

    std::complex<double> zero(0.0, 0.0);
    std::complex<double> one(1.0, 0.0);

    // [0, 0, 1, 1]
    // [0, 0, 1, 1]
    // [1, 1, 0, 0]
    // [1, 1, 0, 0]
    data[0] = zero;
    data[1] = zero;
    data[2] = one;
    data[3] = one;

    data[4] = zero;
    data[5] = zero;
    data[6] = one;
    data[7] = one;

    data[8] = one;
    data[9] = one;
    data[10] = zero;
    data[11] = zero;

    data[12] = one;
    data[13] = one;
    data[14] = zero;
    data[15] = zero;

    algorithms::fft2D(data, sideLength);

    for (int i=0; i<sideLength; i++)
        BOOST_CHECK_EQUAL(data[i], std::complex<double>(2.0, 0.0));

    for (int i=2*sideLength; i<2*sideLength+sideLength; i++)
        BOOST_CHECK_EQUAL(data[i], std::complex<double>(0.0, 0.0));

    double epsilon = 0.001;
    BOOST_CHECK( std::abs(std::real(data[4])) - 1.0 < epsilon);
    BOOST_CHECK( std::abs(std::imag(data[4])) - 1.0 < epsilon);
    BOOST_CHECK( std::abs(std::real(data[5])) - 1.0 < epsilon);
    BOOST_CHECK( std::abs(std::imag(data[5])) - 1.0 < epsilon);
    BOOST_CHECK( std::abs(std::real(data[6])) - 1.0 < epsilon);
    BOOST_CHECK( std::abs(std::imag(data[6])) - 1.0 < epsilon);
    BOOST_CHECK( std::abs(std::real(data[7])) - 1.0 < epsilon);
    BOOST_CHECK( std::abs(std::imag(data[7])) - 1.0 < epsilon);

    BOOST_CHECK( std::abs(std::real(data[12])) - 1.0 < epsilon);
    BOOST_CHECK( std::abs(std::imag(data[12])) - 1.0 < epsilon);
    BOOST_CHECK( std::abs(std::real(data[13])) - 1.0 < epsilon);
    BOOST_CHECK( std::abs(std::imag(data[13])) - 1.0 < epsilon);
    BOOST_CHECK( std::abs(std::real(data[14])) - 1.0 < epsilon);
    BOOST_CHECK( std::abs(std::imag(data[14])) - 1.0 < epsilon);
    BOOST_CHECK( std::abs(std::real(data[15])) - 1.0 < epsilon);
    BOOST_CHECK( std::abs(std::imag(data[15])) - 1.0 < epsilon);

    delete[] data;
}

BOOST_AUTO_TEST_CASE( two_dimensional_fft_3 )
{
    int sideLength = 4;
    std::complex<double>* data = utils::initNewComplexArray(sideLength*sideLength);

    for (int y=0; y<sideLength; y++)
    {
        for (int x=0; x<sideLength; x++)
            data[y*sideLength + x] = std::polar((x+1)*1.0, 0.0);
    }

// print the matrix:
//    for (int y=0; y<sideLength; y++)
//    {
//        for (int x=0; x<sideLength; x++)
//            std::cout << data[y*sideLength + x] << " ";
//        std::cout << std::endl;
//    }

//    std::cout << std::endl;

    algorithms::fft2D(data, sideLength);

// print the matrix
//    for (int y=0; y<sideLength; y++)
//    {
//        for (int x=0; x<sideLength; x++)
//            std::cout << data[y*sideLength + x] << " ";
//        std::cout << std::endl;
//    }

    BOOST_CHECK_EQUAL(data[0], std::polar(4.0, 0.0));
    BOOST_CHECK_EQUAL(data[1], std::polar(8.0, 0.0));
    BOOST_CHECK_EQUAL(data[2], std::polar(12.0, 0.0));
    BOOST_CHECK_EQUAL(data[3], std::polar(16.0, 0.0));

    delete[] data;
}

BOOST_AUTO_TEST_SUITE_END()
