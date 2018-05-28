#include "Ray.hpp"
#include <iostream>

Ray::Ray(Vector *position, Vector *direction){
  this->position = position;
  this->direction = direction;
}

Ray::~Ray(){
  delete position;
  delete direction;
}

bool Ray::Intersects(Sphere *S){

  Vector ray_to_sphere = *(S->Position()) - *(this->position);

  float ray_magnitude = this->direction->Magnitude();

  Vector proj =  (*(this->direction)) * (ray_to_sphere * (*(this->direction))) / (ray_magnitude * ray_magnitude);

  // Case inside the sphere
  if(ray_to_sphere.Magnitude() <= S->Radius())
    return true;

  // Case outside the sphere but looking towards the sphere
  else if(ray_to_sphere * (*(this->direction)) >= 0 && (ray_to_sphere - proj).Magnitude() <= S->Radius())
    return true;

  else
    return false;

}
