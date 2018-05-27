#ifndef RAY_H_
#define RAY_H_

#include "Vector.hpp"
#include "Sphere.hpp"

class Ray {

  private:
    Vector position;
    Vector direction;

  public:
    bool Intersects(Sphere *S);
};

#endif
