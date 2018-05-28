#include "Ray.hpp"

Ray::Ray(Vector *position, Vector *direction){
  this->position = position;
  this->direction = direction;
}

Ray::~Ray(){
  delete position;
  delete direction;
}

bool Ray::Intersects(Sphere *S){

  Vector sphere_to_ray = *(S->Position()) - *(this->position);

  float ray_magnitude = this->direction->Magnitude();

  Vector proj =  *(this->direction) * (sphere_to_ray * *(this->direction)) / (ray_magnitude * ray_magnitude);

  if((sphere_to_ray - proj).Magnitude() > S->Radius())
    return false;

  else if (sphere_to_ray * proj < 0)
    return false;

  else
    return true;

}
