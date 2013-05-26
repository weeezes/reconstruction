#include <complex>

#include "image.hpp"

namespace simrec {

	/// Namespace that contains all the programs algorithms
    namespace algorithms {
        
        void fft(std::complex<double>* data, unsigned int length);
	    void fft2D(std::complex<double>* data, unsigned int sideLength);

	    void flip2DArray(std::complex<double>* data, unsigned int sideLength);
        
        std::complex<double>* initNewComplexArray(unsigned int size);
        
        std::complex<double>* sliceArray(std::complex<double>* array, unsigned int start, unsigned int stop);
        void splitArrayToEvenAndOdd(std::complex<double>* toSplit, unsigned int length, std::complex<double>* oddResult, std::complex<double>* evenResult);
        
        bool isAPowerOfTwo(unsigned int number);

    }

}
