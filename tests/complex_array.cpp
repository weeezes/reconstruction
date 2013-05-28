#include <boost/test/unit_test.hpp>

#include <complex>
#include <iostream>
#include <exception>

#include "simrec/complex_array.hpp"

using namespace simrec;

BOOST_AUTO_TEST_SUITE( complex_array_test )

BOOST_AUTO_TEST_CASE( init_complex_array )
{
    int size = 4;
    ComplexArray array(size);
    for (int i=0; i<size; i++)
    {
        BOOST_CHECK_EQUAL(array[i], std::polar(0.0, 0.0));
    }
}

BOOST_AUTO_TEST_CASE( slice_complex_array )
{
    int size = 4;
    ComplexArray array(size);

    for (int i=0; i<size; i++)
    {
        array[i] = std::polar(i*1.0, 0.0);
    }

    ComplexArray slice = array.slice(1,2);

    BOOST_CHECK_EQUAL(slice[0], std::polar(1.0, 0.0));
    BOOST_CHECK_EQUAL(slice[1], std::polar(2.0, 0.0));

}

BOOST_AUTO_TEST_SUITE_END();


