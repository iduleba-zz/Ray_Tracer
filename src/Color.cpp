#include "Color.hpp"

Color::Color(int red, int green, int blue){
  this->red = red;
  this->green = green;
  this->blue = blue;
}

Color::Color(Color* color){
  this->red = color->Red();
  this->green = color->Green();
  this->blue = color->Blue();
}
