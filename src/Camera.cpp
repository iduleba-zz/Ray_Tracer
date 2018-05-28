#include "Camera.hpp"

float Camera::screen_width = 800;
float Camera::screen_height = 600;

Camera::Camera(Vector position, Vector target) : Camera(position, target, Vector(0,0,1)) {

}

Camera::Camera(Vector position, Vector target, Vector up) {

  this->position = position;
  this->target = target;

  this->up = up;

}

Camera::Camera(Vector position, Vector target, Vector up, int screen_width, int screen_height) : Camera(position, target, up) {

  SetScreenDimensions(screen_width, screen_height);

}

Camera::SetScreenDimensions(float screen_width, float screen_height) {

  Camera::screen_width = screen_width;
  Camera::screen_width = screen_width;

}
