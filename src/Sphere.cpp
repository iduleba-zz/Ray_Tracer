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

Vector* Sphere::Normal(Vector at_point) {

  Vector radial = at_point - *(this->position);

  if(fabs(radial.Magnitude() - radius) > 0.0001)
    throw -1;

  else {
    radial.Normalize();
    return new Vector(radial);
  }

}
