#include "Vector.hpp"
#include <math.h>

Vector::Vector(float x, float y, float z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

Vector Vector::operator+(const Vector& v) const {
  Vector u;

  u.x = this->x + v.x;
  u.y = this->y + v.y;
  u.z = this->z + v.z;

  return u;
}

Vector Vector::operator-(const Vector& v) const {
  Vector u;

  u.x = this->x - v.x;
  u.y = this->y - v.y;
  u.z = this->z - v.z;

  return u;
}

Vector Vector::operator*(const float f) const {
  Vector u;

  u.x = this->x * f;
  u.y = this->y * f;
  u.z = this->z * f;

  return u;
}

Vector Vector::operator/(const float f) const {
  Vector u;

  u.x = this->x / f;
  u.y = this->y / f;
  u.z = this->z / f;

  return u;
}

float Vector::operator*(const Vector& v) const {
  float u;

  u = this->x * v.x  + this->y * v.y + this->z * v.z;

  return u;
}

float Vector::Magnitude() const{
  return sqrtf(this->x*this->x + this->y*this->y + this->z*this->z);
}
