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
        
        void fft(ComplexArray& data, unsigned int length);
        void fftRowsOf(ComplexArray& data, unsigned int sideLength);
	    void fft2D(ComplexArray& data, unsigned int sideLength);

        void ifft(ComplexArray& data, unsigned int length);
        void ifftRowsOf(ComplexArray& data, unsigned int length);
	    void ifft2D(ComplexArray& data, unsigned int sideLength);

        Image inverse_radon(Image input, int angleStart, int angleStop, int angleStep);   
        double fromXYtoSinogramR(double inputMidY, double outputMidY, int x, int y, double rad);
        double angleToXconversionFactor(int width, int angleStart, int angleStop); 
        
		void rampFilter(ComplexArray& data, int width, int height, double slope);
		void lowPassFilter(ComplexArray& data, int width, int height, double slope);
    }

}

#endif
