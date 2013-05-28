#ifndef COMPLEX_ARRAY_H
#define COMPLEX_ARRAY_H

#include <complex>

#include "utils.hpp"

namespace simrec {

/// An array with a fixed size containing complex values
class ComplexArray {

public:
    ComplexArray(int size);
    ComplexArray(const ComplexArray& other);
    ~ComplexArray();

    int getSize() const;
    std::complex<double> get(int index) const;
    std::complex<double>* toArray() const;

    ComplexArray slice(int start, int stop) const;

    std::complex<double>& operator[] (const int index);
    ComplexArray& operator=(const ComplexArray& other);

private:
    std::complex<double>* array;

    int size;

};

}

#endif
