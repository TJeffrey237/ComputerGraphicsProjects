#include "../include/ppm.h"

bool PPMImage::readPPM(const std::string &filename) {
    // c_str is used to convert the string to a list of chars
    FILE* fp = fopen(filename.c_str(), "r");
    if(fp == NULL) {
        fprintf(stderr, "Error: File %s could not be opened.\n", filename.c_str());
        return false;
    }

    char magic[3];
    if(fscanf(fp, "%2s", magic) != 1 || strcmp(magic, "P3") != 0) {
        fprintf(stderr, "Error: File magic number does not match P3.\n");
        fclose(fp);
        return false;
    }

    skipComments(fp);
    if(fscanf(fp, "%d", &width) != 1) {
        fprintf(stderr, "Error: Could not read the width.\n");
        fclose(fp);
        return false;
    }

    skipComments(fp);
    if(fscanf(fp, "%d", &height) != 1) {
        fprintf(stderr, "Error: Could not read the height.\n");
        fclose(fp);
        return false;
    }

    skipComments(fp);
    if(fscanf(fp, "%hhu", &maxColor) != 1) {
        fprintf(stderr, "Error: Could not read the max color.\n");
        fclose(fp);
        return false;
    }

    pixels.resize(width * height * 3);
    for(int i = 0; i < width * height * 3; i++) {
        if(fscanf(fp, "%hhu", &pixels[i]) != 1) {
            fprintf(stderr, "Error: Could not read pixel data.\n");
            fclose(fp);
            return false;
        }
        if(pixels[i] < 0 || pixels[i] > maxColor) {
        fprintf(stderr, "Error: Pixel value %hhu at index %hhu is out of range (0-%hhu).\n", pixels[i], i, maxColor);
        fclose(fp);
        return false;
    }
    }

    fclose(fp);
    return true;
}

bool PPMImage::writePPM(const std::string &filename) const {
    FILE* fp = fopen(filename.c_str(), "w");
    if(fp == NULL) {
        fprintf(stderr, "Error: Could not open %s for writing.\n", filename.c_str());
        return false;
    }

    fprintf(fp, "P3\n");
    fprintf(fp, "%d %d\n", width, height);
    fprintf(fp, "%d\n", maxColor);

    for(size_t i = 0; i < pixels.size(); i += 3) {
        fprintf(fp, "%d     %d     %d\n", pixels[i], pixels[i + 1], pixels[i + 2]);
    }

    fclose(fp);
    return true;
}

void PPMImage::applyGaussianBlur(const PPMImage &input) {
    if(input.width < 5 || input.height < 5) {
        this->pixels = input.pixels;
        return;
    }

    this->width = input.width;
    this->height = input.height;
    this->maxColor = input.maxColor;
    this->pixels.resize(input.pixels.size());

    // kernel from the slides
    int kernel[5][5] = {
        {1, 2, 3, 2, 1},
        {2, 4, 6, 4, 2},
        {3, 6, 9, 6, 3},
        {2, 4, 6, 4, 2},
        {1, 2, 3, 2, 1}
    };

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;
            // iterating through the neighborhood
            for(int ny = -2; ny <= 2; ny++) {
                for(int nx = -2; nx <= 2; nx++) {
                    int cx = x + nx;
                    int cy = y + ny;

                    // mirroring for out of bounds neighbors
                    if(cx < 0) {
                        cx = -cx;
                    }
                    else if(cx >= width) {
                        cx = 2 * (width - 1) - cx;
                    }
                    if(cy < 0) {
                        cy = -cy;
                    }
                    else if(cy >= height) {
                        cy = 2 * (height - 1) - cy;
                    }

                    int neighbor = (cy * width + cx) * 3;
                    int weight = kernel[ny + 2][nx + 2];

                    sumR += input.pixels[neighbor] * weight;
                    sumG += input.pixels[neighbor + 1] * weight;
                    sumB += input.pixels[neighbor + 2] * weight;
                }
            }
            int target = (y * width + x) * 3;
            this->pixels[target] = sumR / 81;
            this->pixels[target + 1] = sumG / 81;
            this->pixels[target + 2] = sumB / 81;
        }
    }
}

void PPMImage::skipComments(FILE* fp) {
    int ch;
    while((ch = fgetc(fp)) != EOF) {
        if(isspace(ch)) {
            continue;
        }
        else if(ch == '#') {
            while((ch = fgetc(fp)) != EOF && ch != '\n');
        }
        else {
            ungetc(ch, fp);
            break;
        }
    }
}