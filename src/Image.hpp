#ifndef IMAGE_H_
#define IMAGE_H_

#include "Color.hpp"
#include <fstream>

class Image {

  private:
    int width;
    int height;
    Color** image;

  public:
    Image(int width, int height);
    ~Image();

    int ImageWidth() const { return width; };
    int ImageHeight() const { return height; };
    void ImageSet(unsigned i, Color *color);

    //print image to a PPM file
    //http://manpages.ubuntu.com/manpages/xenial/man5/ppm.5.html
    void ExportPPM(const char* fileName);

};

#endif
