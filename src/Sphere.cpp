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
