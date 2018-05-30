#include "Image.hpp"

Image::Image(int width, int height){
  this->width = width;
  this->height = height;
  this->image = new Color*[width*height];
}

Image::Image(int width, int height, unsigned int* unrolledTable) : Image(width, height){
  for (unsigned i = 0; i < width * height; ++i) {
    image[i] = new Color(unrolledTable[3 * i], unrolledTable[3 * i + 1], unrolledTable[3 * i + 2]);
  }
}

Image::~Image(){
  if(this->image!=NULL){
    for (unsigned i = 0; i < width * height; ++i) {
      delete image[i];
    }
    delete[] image;
  }
}

void Image::ImageSet(unsigned i, Color *color) {
  if (i>=width*height) throw -i;
  this->image[i] = color;
}

unsigned int* Image::ToArray() const {
  unsigned int* unrolledTable = new unsigned int[3 * width * height];
  for (unsigned i = 0; i < width * height; ++i) {
    unrolledTable[3*i] = (unsigned int) image[i]->Red();
    unrolledTable[3*i+1] = (unsigned int) image[i]->Green();
    unrolledTable[3*i+2] = (unsigned int) image[i]->Blue();
  }
  return unrolledTable;
}

Image Image::operator+(const Image& other) const {
  if(this->width != other.width || this->height != other.height)
    std::cerr << "Error adding images: Sizes aren't consistent!" << endl;

  Image img = Image(width, height);
  for (unsigned i = 0; i < width * height; ++i) {
    img.image[i] = new Color(*(this->image[i]) + *(other.image[i]));
  }
  return img;
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
