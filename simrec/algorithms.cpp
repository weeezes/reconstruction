#include "algorithms.hpp"

using namespace simrec;

/// Fast Fourier Transform, based on the Cooley-Tukey algorithm
/**
* Calculates the Fourier transform of the input data in place.
* @param data input data to transform
* @param length length of the data, must be a value that is a power of two.
*/
void algorithms::fft(ComplexArray& data, int i, unsigned int length)
{
    if (length == 1)
        return;

    if (!utils::isAPowerOfTwo(length))
        throw "Not a power of two!";

    ComplexArray even(length/2);
    ComplexArray odd(length/2);

    utils::splitArrayToEvenAndOdd(data, length, odd, even);

    algorithms::fft(even, 0, length/2);
    algorithms::fft(odd, 0, length/2);

    for (int k=0; k<=length/2-1; k++)
    {
        data[k] = even[k] + odd[k]*std::polar(1.0, -2*3.14*k/length);
        data[k+length/2] = even[k] - odd[k]*std::polar(1.0, -2*3.14*k/length);
    }
    
}

/// Fast Fourier Transform in two dimensions, based on the Cooley-Tukey algorithm
/**
* Calculates the Fourier transform of the 2d input data in place.
* @param data the input data to transform
* @param sideLength the sides length of the rectangular data. Must be a value that
* is a power of two
*/
void algorithms::fft2D(ComplexArray& data, unsigned int sideLength)
{
    if (!utils::isAPowerOfTwo(sideLength))
        throw "Not a power of two!";

    for (int y=0; y<sideLength; y++)
    { 
		ComplexArray slice = data.slice(y*sideLength, y*sideLength+sideLength-1);
        algorithms::fft(slice, 0, sideLength);
		for (int i=0; i<sideLength; i++)
		{
			data[y*sideLength+i] = slice[i];
		}
    }

    utils::flip2DArray(data, sideLength);

    for (int y=0; y<sideLength; y++)
    { 
		ComplexArray slice = data.slice(y*sideLength, y*sideLength+sideLength-1);
        algorithms::fft(slice, 0, sideLength);
		for (int i=0; i<sideLength; i++)
		{
			data[y*sideLength+i] = slice[i];
		}
    }

    utils::flip2DArray(data, sideLength);
}

/// Inverse Fast Fourier Transform, based on the Cooley-Tukey algorithm
/**
* Calculates the Inverse Fourier transform of the input data in place.
* @param data input data to transform
* @param length length of the data, must be a value that is a power of two.
*/
void algorithms::ifft(ComplexArray& data, int i, unsigned int length)
{
    if (length == 1)
        return;

    if (!utils::isAPowerOfTwo(length))
        throw "Not a power of two!";

    ComplexArray even(length/2);
    ComplexArray odd(length/2);

    utils::splitArrayToEvenAndOdd(data, length, odd, even);

    algorithms::ifft(even, 0, length/2);
    algorithms::ifft(odd, 0, length/2);

    for (int k=0; k<=length/2-1; k++)
    {
        data[k] = even[k] + odd[k]*std::polar(1.0, 2*utils::PI*k/length);
        data[k+length/2] = even[k] - odd[k]*std::polar(1.0, 2*utils::PI*k/length);
    }
}

/// Inverse Fast Fourier Transform in two dimensions, based on the Cooley-Tukey algorithm
/**
* Calculates the Inverse Fourier transform of the 2d input data in place.
* @param data the input data to transform
* @param sideLength the sides length of the rectangular data. Must be a value that
* is a power of two
*/
void algorithms::ifft2D(ComplexArray& data, unsigned int sideLength)
{
    if (!utils::isAPowerOfTwo(sideLength))
        throw "Not a power of two!";


    for (int y=0; y<sideLength; y++)
    { 
		ComplexArray slice = data.slice(y*sideLength, y*sideLength+sideLength-1);
        algorithms::ifft(slice, 0, sideLength);
		for (int i=0; i<sideLength; i++)
		{
			data[y*sideLength+i] = slice[i];
		}
        
		// normalization
        for (int i=y*sideLength; i<y*sideLength+sideLength; i++)
            data[i] = data[i]/std::complex<double>(sideLength, 0.0);
    }

    utils::flip2DArray(data, sideLength);

    for (int y=0; y<sideLength; y++)
    { 
		ComplexArray slice = data.slice(y*sideLength, y*sideLength+sideLength-1);
        algorithms::ifft(slice, 0, sideLength);
		for (int i=0; i<sideLength; i++)
		{
			data[y*sideLength+i] = slice[i];
		}

        // normalization
        for (int i=y*sideLength; i<y*sideLength+sideLength; i++)
            data[i] = data[i]/std::complex<double>(sideLength, 0.0);
    }

    utils::flip2DArray(data, sideLength);
}

Image algorithms::inverse_radon(Image input, int angleStart, int angleStop, int angleStep)
{
    // estimate output width
    int outputWidth = (int) (2*std::floor(input.getHeight()/(2*std::sqrt(2))));

    ComplexArray transformedData(outputWidth*outputWidth);
    ComplexArray inputData = input.getData();

    int inputMidIndex = (int) ( input.getHeight() / 2.0 + 0.5 );
    int outputMidIndex = (int) ( outputWidth / 2.0 + 1.5);
	
	double dt = 1.0*input.getWidth()/(angleStop-angleStart);

    for (int y=0; y<outputWidth; y++)
    {
        for (int x=0; x<outputWidth; x++)
        {
            for (int k=angleStart; k<=angleStop; k+=angleStep)
            {
                double rad = utils::toRadians(k);

                double ra = inputMidIndex + ( x - outputMidIndex )*std::sin(rad) + ( y - outputMidIndex )*std::cos(rad);
				double rb = std::floor(ra);
				
				std::complex<double> w1 = std::complex<double>(ra-rb, ra-rb);
				std::complex<double> w2 = std::complex<double>(1-ra+rb, 1-ra+rb);

				int t = (int) (dt*(k-angleStart) + 0.5);

                if (rb >= 0 && rb < input.getHeight()-1)
				{
                    transformedData[y*outputWidth+x] += w1*inputData[t + rb*input.getWidth()];
					transformedData[y*outputWidth+x] += w2*inputData[t + rb*input.getWidth()+1];

				}
            }

			transformedData[y*outputWidth+x] *= std::complex<double>(1.0/outputWidth, 1.0/outputWidth);
        }
    }

    Image transformed(transformedData, outputWidth, outputWidth);

    return transformed;
}

void algorithms::rampFilter(ComplexArray& data, int width, int height, double slope)
{
	for (int y=0; y<height; y++)
	{
		for (int x=0; x<width; x++)
		{
			int dy = y-height/2;
			int dx = x-width/2;
			double r = std::sqrt(dy*dy+dx*dx);
			data[y*width+x] = data[y*width+x]*std::complex<double>(r*slope, r*slope);
		}
	}
}

void algorithms::lowPassFilter(ComplexArray& data, int width, int height, double cutoff_percentage)
{
	double max_r = std::sqrt(width*width/4+height*height/4);
	double cutoff_r = max_r*cutoff_percentage;

	for (int y=0; y<height; y++)
	{
		for (int x=0; x<width; x++)
		{
			int dy = y-height/2;
			int dx = x-width/2;
			double r = std::sqrt(dy*dy+dx*dx);
			if (r < cutoff_r)
				data[y*width+x] = std::complex<double>(0.0, 0.0);
		}
	}
}
