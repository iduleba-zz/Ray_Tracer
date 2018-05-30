#include "Color.hpp"
#include <algorithm>

Color::Color(int red, int green, int blue){
  this->red = max(0,min(255,red));
  this->green = max(0,min(255,green));
  this->blue = max(0,min(255,blue));
}

Color::Color(Color* color){
  this->red = color->red;
  this->green = color->green;
  this->blue = color->blue;
}

Color::Color(const Color &color){
  this->red = color.red;
  this->green = color.green;
  this->blue = color.blue;
}

Color Color::operator+(const Color& c) const{
  return Color(this->red + c.red, this->green + c.green, this->blue + c.blue);
}

Color Color::operator*(const float& f) const{
  return Color(this->red * f, this->green * f, this->blue * f);
}

void Color::operator+=(const Color& v){
  this->red = this->red + v.red;
  this->green = this->green + v.green;
  this->blue = this->blue + v.blue;
}


Color Color::operator&(const Color& light) const{
  return Color( (this->red * light.red) / 255, (this->green * light.green) / 255, (this->blue * light.blue) / 255);
}
