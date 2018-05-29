#include "Image.hpp"

Image::Image(int width, int height){
  this->width = width;
  this->height = height;
  this->image = new Color*[width*height];;
}

Image::~Image(){
  if(this->image!=NULL){
    for (unsigned i = 0; i < width * height; ++i) {
      delete image[i];
    }
    delete image;
  }
}

// Save PPM image
//fileName should be like "./untitled.ppm"
void Image::ExportPPM(const char* fileName){
  std::ofstream ofs(fileName, std::ios::out | std::ios::binary);
  ofs << "P6\n" << width << " " << height << "\n255\n";
  for (unsigned i = 0; i < width * height; ++i) {
    ofs << (unsigned char) image[i]->Red() << (unsigned char) image[i]->Green() << (unsigned char) image[i]->Blue();
  }
  ofs.close();
}
