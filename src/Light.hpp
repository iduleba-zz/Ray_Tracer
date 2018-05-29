#ifndef LIGHT_H_
#define LIGHT_H_

#include "Vector.hpp"
#include "Color.hpp"

class Light {

  private:
    Vector *position;
    // optionally we can have a non-white colour
    Color *ambient_color;
    Color *diffuse_color;
    Color *specular_color;

  public:
    Light(Vector *position);
    Light(Vector *position, Color *ambient_color, Color *diffuse_color, Color *specular_color);
    ~Light();
    Color *AmbientColor() const { return ambient_color; };
    Color *DiffuseColor() const { return diffuse_color; };
    Color *SpecularColor() const { return specular_color; };
    Vector *Position() const { return position; };
};

#endif
