#include "Light.hpp"

Light::Light(Vector *position) : Light(position, new Color(255,255,255)) {}

Light::Light(Vector *position, Color *color) {
  this->position = position;
  this->color = color;
}

Light::~Light() {
  delete position;
  delete color;
}
