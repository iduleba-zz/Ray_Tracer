#ifndef SPHERE_H_
#define SPHERE_H_

#include "Vector.hpp"

class Sphere {

  public:
    Sphere(Vector position, float radius, float R, float G, float B);
    ~Sphere();
    Vector position;
    float radius;
    float R;
    float G;
    float B;
};

#endif
