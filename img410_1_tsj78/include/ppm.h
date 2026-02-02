#ifndef PPM_H
#define PPM_H

#include <vector>
#include <string>

class PPMImage {
public:
    int width;
    int height;
    int maxColor;
    std::vector<int> pixels;

    PPMImage() : width(0), height(0), maxColor(255) {}

    bool readPPM(const std::string &filename);
    bool writePPM(const std::string &filename) const;
    void applyGaussianBlur(const PPMImage &input);
private:
    void skipComments(FILE* fp);
};

#endif