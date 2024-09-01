#include <iostream>
#include <fitsio.h>  // Include the CFITSIO header

void readFITS(const char* filename) {
    fitsfile* fptr;   // FITS file pointer
    int status = 0;   // CFITSIO status value MUST be initialized to zero!
    int bitpix, naxis;
    long naxes[2] = {1, 1};  // Image width and height

    // Open the FITS file
    if (fits_open_file(&fptr, filename, READONLY, &status)) {
        fits_report_error(stderr, status); // Print error message
        return;
    }

    // Read the NAXIS keyword to find out how many dimensions the image has
    if (fits_get_img_param(fptr, 2, &bitpix, &naxis, naxes, &status)) {
        fits_report_error(stderr, status);
        return;
    }

    // Check if the file is a 2D image
    if (naxis != 2) {
        std::cerr << "Error: the input file is not a 2D image" << std::endl;
        fits_close_file(fptr, &status);
        return;
    }

    long npixels = naxes[0] * naxes[1];  // Total number of pixels in the image
    std::unique_ptr<float[]> pixels(new float[npixels]);  // Allocate memory for the image

    // Read the image data into the array
    long fpixel = 1;  // First pixel to read
    if (fits_read_img(fptr, TFLOAT, fpixel, npixels, NULL, pixels.get(), NULL, &status)) {
        fits_report_error(stderr, status);
        return;
    }

    // Close the FITS file
    if (fits_close_file(fptr, &status)) {
        fits_report_error(stderr, status);
        return;
    }

    // Output some of the pixel values as a demonstration
    for (int i = 0; i < std::min(npixels, 10L); ++i) {
        std::cout << "Pixel " << i + 1 << ": " << pixels[i] << std::endl;
    }
}

int main(int argc, char **argv) {
    if (argc==2)
        readFITS(argv[1]);
    else
        std::cout << "Expected a Filename as a parameter." << std::endl;
    return 0;
}
