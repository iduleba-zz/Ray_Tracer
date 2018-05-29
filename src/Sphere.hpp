#ifndef SPHERE_H_
#define SPHERE_H_

#include "Vector.hpp"
#include "Color.hpp"
#include <cmath>

#define AMBIENT 0
#define DIFFUSE 1
#define SPECULAR 2
#define SHININESS 3

class Sphere {

  public:
    Sphere(Vector *position, float radius, Color *color, float ka, float kd, float ks, float sh);
    ~Sphere();

    Vector* Position() const { return position;};
    float Radius() const { return radius;};
    Color* Color_() const { return color;};
    float* ReflectionConstants() const {return reflection_constants;};

    Vector Normal(Vector atPoint);

  private:
    Vector *position;
    float radius;
    Color *color;
    float *reflection_constants;
};

#endif
