#ifndef SPHERE_H_
#define SPHERE_H_

#include "Vector.hpp"

class Sphere {

  public:
    Sphere(Vector position, float radius, Color color);
    ~Sphere();
    Vector position;
    float radius;
    Color color;
};

#endif
