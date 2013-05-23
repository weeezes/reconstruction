#include <complex>

#include "image.hpp"

namespace simrec {

    namespace algorithms {
        
        void fft(std::complex<double>* data, unsigned int length);
        std::complex<double>* initNewComplexArray(unsigned int size);
        void splitArrayToEvenAndOdd(std::complex<double>* toSplit, unsigned int length, std::complex<double>* oddResult, std::complex<double>* evenResult);
        bool isAPowerOfTwo(unsigned int number);

    }

}
