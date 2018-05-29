#include "Ray.hpp"

Ray::Ray(Vector position, Vector direction){
  this->position = position;
  this->direction = direction;
  this->direction.Normalize();
}

bool Ray::Intersects(Sphere *S, float *t1, float *t2){

  Vector ray_to_sphere = *(S->Position()) - this->position;

  Vector proj = this->direction * (ray_to_sphere * (this->direction));

  float proj_magnitude = proj.Magnitude();
  float orth_magnitude = (ray_to_sphere - proj).Magnitude();

  // Solve (x - sphere.position.x)^2 + (y - sphere.position.y)^2 + (y - sphere.position.y)^2 = r^2;
  // with (x,y,z) = ray.position + t * ray.direction;

  // Resulting equation:
  // t² * ray.dir² - 2 t * ray.dir * (ray.pos - sphere.pos) + (ray.pos - sphere.pos)² - r² = 0
  // t² - 2 * t * proj.Magnitude() + ray_to_sphere.Magnitude()² - r² = 0
  // delta/4a = proj.Magnitude()² - (ray_to_sphere.Magnitude()² - r²) = r² - orth.Magnitude()²
  // t = proj.Magnitude() / ray_magnitude +- sqrt(delta/4a)
  float delta;

  // Case inside the sphere
  if(ray_to_sphere.Magnitude() <= S->Radius()) {

    delta = S->Radius() * S->Radius() - orth_magnitude * orth_magnitude;
    *t2 = proj_magnitude - sqrtf(delta);
    *t1 = proj_magnitude + sqrtf(delta);

    return true;
  }

  // Case outside the sphere but looking towards the sphere
  else if(ray_to_sphere * (this->direction) >= 0 && orth_magnitude <= S->Radius()){

    delta = S->Radius() * S->Radius() - orth_magnitude * orth_magnitude;
    *t1 = proj_magnitude - sqrtf(delta);
    *t2 = proj_magnitude + sqrtf(delta);

    return true;
  }

  else

    return false;

}
