#include "Vector.hpp"

Vector Vector::operator+(const Vector& v) const {
  Vector u;

  u.x = this->x + v.x;
  u.y = this->y + v.y;
  u.z = this->z + v.z;

  return u;
}
