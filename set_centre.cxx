#include <iostream>
#include <fitsio.h>  // Include the CFITSIO header

/* Simple Set Header value in FITS file.
 *
 * Note: No data range checking currently done.
 *
 * Build:
 *  g++ set_centre.cxx -o set_centre -I /usr/local/include/fits -L/usr/local/lib -l cfitsio
 *
 * Use:
 *   ./set_centre TEST1.fits 23.2 -21.2
 *
 *
*/

void readPixels(const char* filename) {
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
    if (naxis < 2) {
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



void readHeader(const char* filename)
{
    fitsfile* fptr;   // FITS file pointer
    int status = 0;   // CFITSIO status value MUST be initialized to zero!

    // Open the FITS file
    if (fits_open_file(&fptr, filename, READONLY, &status)) {
        fits_report_error(stderr, status); // Print error message
        return;
    }

    // Read and display header data
    char card[FLEN_CARD];  // Buffer to hold each header card (80 characters)
    int nkeys, keypos;

    // Get number of keywords in the primary header
    if (fits_get_hdrspace(fptr, &nkeys, NULL, &status)) {
        fits_report_error(stderr, status);
        fits_close_file(fptr, &status);
        return;
    }

    std::cout << "Header data:" << std::endl;
    std::string line;
    // Loop through each keyword in the header
    for (keypos = 1; keypos <= nkeys; keypos++) {
        if (fits_read_record(fptr, keypos, card, &status)) {
            fits_report_error(stderr, status);
            break;
        }
        line=card;
        std::cout << line << std::endl;  // Print each header card
    }
}



void setCenter(const char* filename, float ra,  float dec  )
{
    fitsfile* fptr;   // FITS file pointer
    const char* k1 = "RA";                   // Keyword name (max 8 characters)
    const char* k1comm="RA in DEGREES";
    const char* k2 = "DEC";                   // Keyword name (max 8 characters)
    const char* k2comm="DECLINATION in DEGREES";

    int status = 0;   // CFITSIO status value MUST be initialized to zero!
    // Open the FITS file with read/write access
    if (fits_open_file(&fptr, filename, READWRITE, &status)) {
        fits_report_error(stderr, status); // Print error message
        return;
    }

    if (fits_update_key(fptr, TFLOAT, k1, &ra,
                       k1comm, &status))
    {
        fits_report_error(stderr, status);
    } else {
        std::cout << "\nAdded new keyword to header: " << k1 << " = " << ra << " / " << k1comm << std::endl;
    }

    if (fits_update_key(fptr, TFLOAT, k2, &dec,
                        k2comm, &status))
    {
        fits_report_error(stderr, status);
    } else {
        std::cout << "\nAdded new keyword to header: " << k2 << " = " << dec << " / " << k2comm << std::endl;
    }

    // Close the FITS file
    if (fits_close_file(fptr, &status)) {
        fits_report_error(stderr, status);
        return;
    }
    std::cout << "File successfully closed." << std::endl;
}

int main(int argc, char **argv) {
    if (argc==4)
    {
        setCenter(argv[1],atof(argv[2]),atof(argv[3]));
        readHeader(argv[1]);
    }
    else
        std::cout << "Expected a FILENAME RA DEC as parameters." << std::endl;
    return 0;
}
