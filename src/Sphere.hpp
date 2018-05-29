#ifndef SPHERE_H_
#define SPHERE_H_

#include "Vector.hpp"
#include "Color.hpp"
#include <cmath>

#define SPECULAR 0
#define DIFUSE 1
#define AMBIENT 2
#define SHININESS 3

class Sphere {

  public:
    Sphere(Vector *position, float radius, Color *color, float ks, float kd, float ka, float sh);
    ~Sphere();

    Vector* Position() const { return position;};
    float Radius() const { return radius;};
    Color* Color_() const { return color;};
    float* ReflectionConstants() const {return reflection_constants;};

    Vector* Normal(Vector atPoint);

  private:
    Vector *position;
    float radius;
    Color *color;
    float *reflection_constants;
};

#endif
