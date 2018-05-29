#include "Color.hpp"
#include <algorithm>

Color::Color(int red, int green, int blue){
  this->red = red % 256;
  this->green = green % 256;
  this->blue = blue % 256;
}

Color::Color(Color* color){
  this->red = color->red;
  this->green = color->green;
  this->blue = color->blue;
}

Color Color::operator+(const Color& c) const{

  return Color(this->red + c.red, this->green + c.green, this->blue + c.blue);

}

Color Color::operator*(const float& f) const {

  return Color(this->red * f, this->green * f, this->blue * f);

}
