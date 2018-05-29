#include "Sphere.hpp"
#include <cmath>

Sphere::Sphere(Vector *position, float radius, Color *color) {
  this->position = position;
  this->radius = radius;
  this->color = color;
}

Sphere::~Sphere() {
  delete position;
  delete color;
}

Vector* Normal(Vector at_point) {

  Vector* radial = at_point - position;

  if(fabs(radial.Magnitude() - radius) < 0.0001)
    return nullptr;

  else {
    radial->Normalize();
    return radial;
  }

}
