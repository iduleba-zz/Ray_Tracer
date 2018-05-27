#include "Ray.hpp"

bool Ray::Intersects(Sphere *S){

  Vector sphere_to_ray = S->GetPosition() - this->position;

  float ray_magnitude = this->direction.Magnitude();

  Vector proj =  this->direction * (sphere_to_ray * this->direction) / (ray_magnitude * ray_magnitude);

  if((sphere_to_ray - proj).Magnitude() > S->GetRadius())
    return false;

  else if (sphere_to_ray * proj < 0)
    return false;

  else
    return true;

}
