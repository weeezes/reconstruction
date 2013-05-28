#include "complex_array.hpp"

using namespace simrec;

ComplexArray::ComplexArray(int size)
{
    this->size = size;
    this->array = utils::initNewComplexArray(size);
}

ComplexArray::ComplexArray(const ComplexArray& other)
{
    this->size = other.getSize();
    this->array = other.toArray();
}

ComplexArray::~ComplexArray()
{
    delete[] this->array;
}

int ComplexArray::getSize() const
{
    return this->size;
}

std::complex<double> ComplexArray::get(int index) const
{
    if (index < 0 || index > getSize()-1)
        throw "Index out of range!";

    return this->array[index];
}

/// Generates a raw array copy from the object
/**
 * @return an array of the type std::complex<double>
 */
std::complex<double>* ComplexArray::toArray() const
{
    std::complex<double>* copy = utils::initNewComplexArray(this->size);

    for (int i=0; i<this->size; i++)
        copy[i] = this->array[i];
        
    return copy;
}

/// Slices a part of the array
/**
 * Creates a slice from the array from the index defined by start to the index
 * defined by stop. Stop must be a value larger than start, and both indices
 * must be inside the limit [0, size-1]
 *
 * @param start the index where to start slicing
 * @param stop the index where to stop slicing
 * @return a slice from the original array
 */
ComplexArray ComplexArray::slice(int start, int stop) const
{
    if (stop <= start)
        throw "Stop can't be lower than start!";
    
    if (stop < 0 || start < 0 || stop > getSize()-1 || stop > getSize()-1)
        throw "Index out of range!";

    ComplexArray s(stop - start + 1);

    for (int i=start, k=0; i<=stop; i++, k++)
    {
        double real = std::real(this->array[i]);
        double imag = std::imag(this->array[i]);
        s[k] = std::complex<double>(real, imag);
    }

    return s;
}

std::complex<double>& ComplexArray::operator[](const int index)
{
    if ( index < 0 || index > getSize()-1)
        throw "Index out of range!";

    return this->array[index];
}

ComplexArray& ComplexArray::operator=(const ComplexArray& other)
{
    this->size = other.getSize();
    this->array = other.toArray();

    return *this;
}

