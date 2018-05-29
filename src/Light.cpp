#include "Light.hpp"

Light::Light(Vector *position) : Light(position, new Color(255,255,255)) {}

Light::Light(Vector *position, Color *ambient_color, Color *diffuse_color, Color *specular_color) {
  this->position = position;
  this->ambient_color = ambient_color;
  this->diffuse_color = diffuse_color;
  this->specular_color specular_color;
}

Light::~Light() {
  delete position;
  delete ambient_color;
  delete diffuse_color;
  delete specular_color;
}
