#include "Light.hpp"

Light::Light(Vector position) {

  this->position = position;

}


Light::Light(Vector position, Color color) {

  this->position = position;
  this->color = color;
  
}
