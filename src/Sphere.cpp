#include "Sphere.hpp"


Sphere::Sphere(Vector *position, float radius, Color *color, float ka, float kd, float ks, float sh) {
  this->position = position;
  this->radius = radius;
  this->color = color;
  reflection_constants = new float[4];
  reflection_constants[0] = ka;
  reflection_constants[1] = kd;
  reflection_constants[2] = ks;
  reflection_constants[3] = sh;
}

Sphere::~Sphere() {
  delete position;
  delete color;
  delete[] reflection_constants;
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
