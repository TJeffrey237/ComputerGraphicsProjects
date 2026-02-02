#include <stdio.h>
#include <stdint.h>
#include "../include/ppm.h"

int main(int argc, char **argv) {
    if(argc != 3) {
        fprintf(stderr, "Error: Incorrect number of arguments provided.\nProper Arguments: input_file.ppm output_file.ppm\n");
        return 1;
    }

    PPMImage inputImg;
    PPMImage blurredImg;

    // TODO 1: READ THE FILE
    if(!inputImg.readPPM(argv[1])) {
        return 1;
    }

    // TODO 2: Apply Gaussian Blur
    blurredImg.applyGaussianBlur(inputImg);

    // TODO 3: Write to output file
    if(!blurredImg.writePPM(argv[2])) {
        return 1;
    }

    return 0;
}