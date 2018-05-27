#include "Vector.hpp"

Vector Vector::operator+(const Vector& v) const {
  Vector u;

  u.x = this->x + v.x;
  u.y = this->y + v.y;
  u.z = this->z + v.z;

  return u;
}

Vector Vector::operator*(const float f) const {
  Vector u;

  u.x = this->x * f;
  u.y = this->y * f;
  u.z = this->z * f;

  return u;
}
