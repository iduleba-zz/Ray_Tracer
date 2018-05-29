#include "Sphere.hpp"

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

  if(radial.Magnitude() != radius)
    return nullptr;

  else {
    radial->Normalize();
    return radial;
  }

}
