#ifndef IMAGE_H_
#define IMAGE_H_

#include "Color.hpp"
#include <fstream>
#include <iostream>

class Image {

  private:
    int width;
    int height;
    Color** image;

  public:
    Image(int width, int height);
    Image(const Image &img);
    Image(int width, int height, unsigned int* unrolledTable);
    ~Image();

    int ImageWidth() const { return width; };
    int ImageHeight() const { return height; };
    void ImageSet(unsigned i, Color *color);

    //print image to a PPM file
    //http://manpages.ubuntu.com/manpages/xenial/man5/ppm.5.html
    void ExportPPM(const char* fileName);

    unsigned int* ToArray() const;

    Image operator+(const Image& img) const;
};

#endif
