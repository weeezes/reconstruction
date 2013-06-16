#include "algorithms.hpp"

using namespace simrec;

/// Fast Fourier Transform, based on the Cooley-Tukey algorithm
/**
* Calculates the Fourier transform of the input data.
* @param data input data to transform
* @param length length of the data, must be a value that is a power of two.
*/
void algorithms::fft(ComplexArray& data, unsigned int length)
{
    if (length == 1)
        return;

    if (!utils::isAPowerOfTwo(length))
        throw "Not a power of two!";

    ComplexArray even(length/2);
    ComplexArray odd(length/2);

    utils::splitArrayToEvenAndOdd(data, length, odd, even);

    algorithms::fft(even, length/2);
    algorithms::fft(odd, length/2);

    for (int k=0; k<=length/2-1; k++)
    {
        data[k] = even[k] + odd[k]*std::polar(1.0, -2.0*3.14*k/length);
        data[k+length/2] = even[k] - odd[k]*std::polar(1.0, -2.0*3.14*k/length);
    }
    
}

///Take FFT of the data row by row
void algorithms::fftRowsOf(ComplexArray& data, unsigned int sideLength)
{
    for (int y=0; y<sideLength; y++)
    { 
		ComplexArray slice = data.slice(y*sideLength, y*sideLength+sideLength-1);
        
        algorithms::fft(slice, sideLength);

        data.replaceRegionWith(slice, y*sideLength);
    }
}

/// Fast Fourier Transform in two dimensions, based on the Cooley-Tukey algorithm
/**
* Calculates the Fourier transform of the 2d input data.
* @param data the input data to transform
* @param sideLength the sides length of the rectangular data. Must be a value that
* is a power of two
*/
void algorithms::fft2D(ComplexArray& data, unsigned int sideLength)
{
    if (!utils::isAPowerOfTwo(sideLength))
        throw "Not a power of two!";

    fftRowsOf(data, sideLength);

    utils::flip2DArray(data, sideLength);

    fftRowsOf(data, sideLength);

    utils::flip2DArray(data, sideLength);
}

/// Inverse Fast Fourier Transform, based on the Cooley-Tukey algorithm
/**
* Calculates the Inverse Fourier transform of the input data.
* @param data input data to transform
* @param length length of the data, must be a value that is a power of two.
*/
void algorithms::ifft(ComplexArray& data, unsigned int length)
{
    if (length == 1)
        return;

    if (!utils::isAPowerOfTwo(length))
        throw "Not a power of two!";

    ComplexArray even(length/2);
    ComplexArray odd(length/2);

    utils::splitArrayToEvenAndOdd(data, length, odd, even);

    algorithms::ifft(even, length/2);
    algorithms::ifft(odd, length/2);

    for (int k=0; k<=length/2-1; k++)
    {
        data[k] = even[k] + odd[k]*std::polar(1.0, 2.0*utils::PI*k/length);
        data[k+length/2] = even[k] - odd[k]*std::polar(1.0, 2.0*utils::PI*k/length);
    }
}

///Take the iFFT of the data row by row
void algorithms::ifftRowsOf(ComplexArray& data, unsigned int sideLength)
{
    for (int y=0; y<sideLength; y++)
    { 
		ComplexArray slice = data.slice(y*sideLength, y*sideLength+sideLength-1);
        
        algorithms::ifft(slice, sideLength);

        data.replaceRegionWith(slice, y*sideLength);
        
		// normalization
        for (int i=y*sideLength; i<y*sideLength+sideLength; i++)
            data[i] = data[i]/std::complex<double>(sideLength, 0.0);
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

    ifftRowsOf(data, sideLength);

    utils::flip2DArray(data, sideLength);

    ifftRowsOf(data, sideLength);

    utils::flip2DArray(data, sideLength);
}

///Inverse Radon transform
/** 
 * Calculates the Inverse Radon transform for the given input data
 * @param input the input data, a sinogram to be transformed
 * @param angleStart the starting angle that describes the angle of the first row in the singoram 
 * @param angleStop the last angle that describes the angle of the last row in the singoram
 * @param angleStep the step that describes how many degrees the original function has rotated when moving a step in the columns of the sinogram
 */
Image algorithms::inverseRadonTransform(Image input, int angleStart, int angleStop, int angleStep)
{
    // estimate output width
    int outputWidth = (int) (2*std::floor(input.getHeight()/(2*std::sqrt(2))));

    ComplexArray transformedData(outputWidth*outputWidth);
    ComplexArray inputData = input.getData();

    double inputMidY = input.getHeight() / 2.0;
    double outputMidY = outputWidth / 2.0;
	
    double dt = angleToXconversionFactor(input.getWidth(), angleStart, angleStop);

    for (int y=0; y<outputWidth; y++)
    {
        for (int x=0; x<outputWidth; x++)
        {
            for (int k=0; k<input.getWidth(); k+=angleStep)
            {
                double rad = utils::toRadians(dt*k);

                double r = fromXYtoSinogramR(inputMidY, outputMidY, x, y, rad);

                int rIndex = utils::round(r);
                if (rIndex >= 0 && rIndex < input.getHeight())
				{
                    std::complex<double> pixel = inputData[k + rIndex*input.getWidth()];
                    transformedData[y*outputWidth+x] += pixel;
				}
            }
        }
    }

    Image transformed(transformedData, outputWidth, outputWidth);

    return transformed;
}

///Convert from image coordinates to sinogram coordinates
/**
 *@param inputMidY the middle row index on the sinogram
 *@param outputMidY the middle row index on the resulting image
 *@param x the x coordinate where to convert from
 *@param y the y coordinate where to convert from
 *@param rad the angle where to convert from
 */
double algorithms::fromXYtoSinogramR(double inputMidY, double outputMidY, int x, int y, double rad)
{
    double xTerm = ( x - outputMidY )*std::sin(rad);
    double yTerm = ( y - outputMidY )*std::cos(rad);
    double ra = inputMidY + xTerm + yTerm;
}

///Calculates the conversion factor from column index to an angle
/* A column may not always represent a rotation of one angle, so this
 * function calculates how many degrees of rotation a step from a column to the next
 * represents.
 * @param width the width of the sinogram
 * @param angleStart the angle which the first column represents
 * @param angleStop the angle which the last column represents
 * */
double algorithms::angleToXconversionFactor(int width, int angleStart, int angleStop)
{
   return 1.0*(angleStop-angleStart)/width;
}

///applies a ramp filter to the given 2D data
void algorithms::rampFilter(ComplexArray& data, int width, int height, double slope)
{
    double max_r = std::sqrt(width*width/4+height*height/4);

	for (int y=0; y<height; y++)
	{
		for (int x=0; x<width; x++)
		{
			int dy = y-height/2;
			int dx = x-width/2;
			double r = max_r - std::sqrt(dy*dy+dx*dx);
			data[y*width+x] *= r*slope;
        }
	}
}

///applies a low pass filter to the given 2D data
void algorithms::lowPassFilter(ComplexArray& data, int width, int height, double cutoff_percentage)
{
	double max_r = std::sqrt(width*width/4+height*height/4);
	double cutoff_r = max_r*cutoff_percentage;

    int cutoffMaxY = (int)(height*cutoff_percentage + 0.5);
    int cutoffMaxX = (int)(width*cutoff_percentage + 0.5);
    int cutoffMinY = height-cutoffMaxY;
    int cutoffMinX = width-cutoffMaxX;

	for (int y=0; y<height; y++)
	{
		for (int x=0; x<width; x++)
		{
            if (x > cutoffMinX && x < cutoffMaxX)
                data[y*width+x] = std::complex<double>(0.0, 0.0);
            if (y > cutoffMinY && y < cutoffMaxY)
                data[y*width+x] = std::complex<double>(0.0, 0.0);
		}
	}
}
