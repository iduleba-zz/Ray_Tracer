#include "Camera.hpp"

float Camera::screen_width = 800;
float Camera::screen_height = 600;

Camera::Camera(Vector position, Vector target) {

  this->position = position;
  this->target = target;

  this->up = Vector(0,0,1);

}

Camera::Camera(Vector position, Vector target, Vector up, float screen_width, float screen_height) {

  this->position = position;
  this->target = target;

  this->up = up;
  SetScreenDimensions(screen_width, screen_height);

}

Camera::SetScreenDimensions(float screen_width, float screen_height) {

  Camera::screen_width = screen_width;
  Camera::screen_width = screen_width;

}
