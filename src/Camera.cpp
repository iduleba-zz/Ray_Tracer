#include "Camera.hpp"

int Camera::screen_width = 800;
int Camera::screen_height = 600;

Camera::Camera(Vector *position, Vector *target) : Camera(position, target, new Vector(0,0,1)) {}

Camera::Camera(Vector *position, Vector *target, Vector *up) {
  this->position = position;
  this->target = target;
  this->up = up;
}

Camera::~Camera(){
  delete position;
  delete target;
  delete up;
}

Camera::Camera(Vector *position, Vector *target, Vector *up, int screen_width, int screen_height) : Camera(position, target, up){
  SetScreenDimensions(screen_width, screen_height);
}

void Camera::SetScreenDimensions(int screen_width, int screen_height){
  Camera::screen_width = screen_width;
  Camera::screen_height = screen_height;
}
