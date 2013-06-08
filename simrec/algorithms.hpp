#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <complex>
#include <cmath>
#include <iostream>

#include "utils.hpp"
#include "image.hpp"

namespace simrec {

	/// Namespace that contains all the programs algorithms
    namespace algorithms {
        
        void fft(std::complex<double>* data, unsigned int length);
	    void fft2D(std::complex<double>* data, unsigned int sideLength);

        void ifft(std::complex<double>* data, unsigned int length);
	    void ifft2D(std::complex<double>* data, unsigned int sideLength);

        Image inverse_radon(Image input, float angleStart, float angleStop, float angleStep);        
    }

}

#endif
