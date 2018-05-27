#include "Vector.hpp"
#include <math.h>

Vector Vector::operator+(const Vector& v) const {
  Vector u;

  u.SetX(this->x + v.GetX());
  u.SetY(this->y + v.GetY());
  u.SetZ(this->z + v.GetZ());

  return u;
}

Vector Vector::operator-(const Vector& v) const {
  Vector u;

  u.SetX(this->x - v.GetX());
  u.SetY(this->y - v.GetY());
  u.SetZ(this->z - v.GetZ());

  return u;
}

Vector Vector::operator*(const float f) const {
  Vector u;

  u.SetX(this->x * f);
  u.SetY(this->y * f);
  u.SetZ(this->z * f);

  return u;
}

Vector Vector::operator/(const float f) const {
  Vector u;

  u.SetX(this->x / f);
  u.SetY(this->y / f);
  u.SetZ(this->z / f);

  return u;
}

float Vector::operator*(const Vector& v) const {
  float u;

  u = this->x * v.GetX() + this->y * v.GetY() + this->z * v.GetZ();

  return u;
}

float Vector::GetX() const{
  return this->x;
}

float Vector::GetY() const{
  return this->y;
}

float Vector::GetZ() const{
  return this->z;
}

void Vector::SetX(float x){
  this->x = x;
}

void Vector::SetY(float y){
  this->y = y;
}

void Vector::SetZ(float z){
  this->z = z;
}

float Vector::Magnitude() const{
  return sqrtf(this->x*this->x + this->y*this->y + this->z*this->z);
}
