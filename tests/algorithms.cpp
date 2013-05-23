#include <boost/test/unit_test.hpp>

#include <complex>
#include <iostream>
#include "simrec/algorithms.hpp"

using namespace simrec;

BOOST_AUTO_TEST_SUITE( algorithm_test )

BOOST_AUTO_TEST_CASE( init_complex_array )
{
    int size = 4;
    std::complex<double>* array = algorithms::initNewComplexArray(size);
    for (int i=0; i<size; i++)
    {
        BOOST_CHECK_EQUAL(array[i], std::polar(0.0, 0.0));
    }

    delete[] array;
}

BOOST_AUTO_TEST_CASE( split_complex_array )
{
    int size = 4;
    std::complex<double>* array = algorithms::initNewComplexArray(size);
    for (int i=0; i<size; i++)
    {
        array[i] = std::polar(i*1.0, 0.0);
    }

    std::complex<double>* even = algorithms::initNewComplexArray(2);
    std::complex<double>* odd = algorithms::initNewComplexArray(2);

    algorithms::splitArrayToEvenAndOdd(array, size, odd, even);

    BOOST_CHECK_EQUAL(even[0], std::polar(0.0, 0.0));
    BOOST_CHECK_EQUAL(even[1], std::polar(2.0, 0.0));
    BOOST_CHECK_EQUAL(odd[0], std::polar(1.0, 0.0));
    BOOST_CHECK_EQUAL(odd[1], std::polar(3.0, 0.0));
    
    delete[] array;
    delete[] even;
    delete[] odd;
}

BOOST_AUTO_TEST_CASE( one_dimensional_fft_1 )
{
    int size = 4;
    std::complex<double>* data = algorithms::initNewComplexArray(4);
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
    std::complex<double>* data = algorithms::initNewComplexArray(4);

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

BOOST_AUTO_TEST_SUITE_END()
