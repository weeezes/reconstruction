#include "complex_array.hpp"

using namespace simrec;

///Default constructor
ComplexArray::ComplexArray(int size)
{
    this->size = size;
    this->array = new std::complex<double>[size];
}

///Initialize a ComplexArray from a raw std::complex<double>* array
ComplexArray::ComplexArray(std::complex<double>* array, int size)
{
    this->array = array;
    this->size = size;
}

///Copy constructor
ComplexArray::ComplexArray(const ComplexArray& other)
{
    this->size = other.getSize();
    this->array = other.toArray();
}

///Destructor
ComplexArray::~ComplexArray()
{
    delete[] this->array;
}

///Returns the size of the array
int ComplexArray::getSize() const
{
    return this->size;
}

///Returns a value that can't change the value inside of the array
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
   std::complex<double>* copy = new std::complex<double>[this->size];
   for (int i=0; i<this->size; i++)
       copy[i] = this->get(i);
       
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

///Replace a region of the ComplexArray with another ComplexArray
/**
 * Replaces a region of the ComplexArray with a smaller replacement
 * ComplexArray, starting from a given index.
 * @param replacement the replacement ComplexArray. Must fit into the other ComplexArray so that replacement.getSize()+regionStart - 1 < the size of this ComplexArray
 * @param regionStart the index where to start the replacing
 */
void ComplexArray::replaceRegionWith(ComplexArray& replacement, int regionStart)
{
    if (replacement.getSize()+regionStart-1 >= getSize())
    {
        throw "The replacement doesn't fit inside of the ComplexArray";
    }

    for (int i=0; i<replacement.getSize(); i++)
    {
        this->array[regionStart + i] = replacement[i];
    }
}

std::complex<double>& ComplexArray::operator[](const int index)
{
    if ( index < 0 || index > getSize()-1)
        throw "Index out of range!";

    return this->array[index];
}

ComplexArray ComplexArray::operator*(const std::complex<double> v)
{
    ComplexArray mult(this->size);

    for (int i=0; i < this->size; i++)
    {
        mult[i] = this->array[i]*v;
    }

    return mult;
}

ComplexArray ComplexArray::operator-(const ComplexArray& other)
{
    if (other.getSize() != this->size)
        throw "Subtracted arrays must be of the same size!";

    ComplexArray sub(this->size);

    for (int i=0; i < this->size; i++)
        sub[i] = this->get(i) - other.get(i);

    return sub;
}

ComplexArray& ComplexArray::operator=(const ComplexArray& other)
{
    this->size = other.getSize();
    this->array = other.toArray();

    return *this;
}

