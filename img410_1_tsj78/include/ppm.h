#ifndef PPM_H
#define PPM_H

#include <stdint.h>
#include <stdio.h>
#include <cstring>
#include <ctype.h>
#include <vector>
#include <string>

class PPMImage {
public:
    int width;
    int height;
    uint8_t maxColor;
    std::vector<uint8_t> pixels;

    PPMImage() : width(0), height(0), maxColor(255) {}

    bool readPPM(const std::string &filename);
    bool writePPM(const std::string &filename) const;
    void applyGaussianBlur(const PPMImage &input);
private:
    void skipComments(FILE* fp);
};

#endif