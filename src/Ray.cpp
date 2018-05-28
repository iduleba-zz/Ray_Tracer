#include "Ray.hpp"
#include <iostream>

Ray::Ray(Vector position, Vector direction){
  this->position = position;
  this->direction = direction;
}

bool Ray::Intersects(Sphere *S, float &t1, float &t2){

  Vector ray_to_sphere = *(S->Position()) - this->position;

  float ray_magnitude = this->direction->Magnitude();

  Vector proj =  this->direction * (ray_to_sphere * (this->direction)) / (ray_magnitude * ray_magnitude);

  // Solve (x - sphere.position.x)^2 + (y - sphere.position.y)^2 + (y - sphere.position.y)^2 = r^2;
  // with (x,y,z) = ray.position + t * ray.direction;

  // Resulting equation:
  // t² * ray.dir² - 2 t * ray.dir * (ray.pos - sphere.pos) + (ray.pos - sphere.pos)² - r² = 0
  // t² * ray_magnitude² - 2 * t * proj.Magnitude() * ray_magnitude + ray_to_sphere.Magnitude()² - r² = 0
  // delta/4a = proj.Magnitude()² - (ray_to_sphere.Magnitude()² - r²) = r² - orth.Magnitude()²
  // t = proj.Magnitude() / ray_magnitude +- sqrt(delta/4a) / ray_magnitude
  float delta;

  // Case inside the sphere
  if(ray_to_sphere.Magnitude() <= S->Radius()) {
    
    delta = radius * radius - orth_magnitude * orth_magnitude;
    t1 = (proj_magnitude - sqrtf(Delta)) / ray_magnitude;
    t2 = (proj_magnitude + sqrtf(Delta)) / ray_magnitude;

    return true;
  }

  // Case outside the sphere but looking towards the sphere
  else if(ray_to_sphere * (this->direction) >= 0 && (ray_to_sphere - proj).Magnitude() <= S->Radius()){

    delta = radius * radius - orth_magnitude * orth_magnitude;
    t1 = (proj_magnitude - sqrtf(Delta)) / ray_magnitude;
    t2 = (proj_magnitude + sqrtf(Delta)) / ray_magnitude;

    return true;
  }

  else
    return false;

}
