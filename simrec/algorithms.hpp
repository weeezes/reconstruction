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
        
        void fft(ComplexArray& data, int i, unsigned int length);
	    void fft2D(ComplexArray& data, unsigned int sideLength);

        void ifft(ComplexArray& data, int i, unsigned int length);
	    void ifft2D(ComplexArray& data, unsigned int sideLength);

        Image inverse_radon(Image input, int angleStart, int angleStop, int angleStep);        
		void rampFilter(ComplexArray& data, int width, int height, double slope);
		void lowPassFilter(ComplexArray& data, int width, int height, double slope);
    }

}

#endif
