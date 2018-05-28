#ifndef RAY_H_
#define RAY_H_

#include "Vector.hpp"
#include "Sphere.hpp"

class Ray {

  public:
    Ray(Vector position, Vector direction);
    ~Ray();
    Vector position;
    Vector direction;
    bool Intersects(Sphere *S);
};

#endif
