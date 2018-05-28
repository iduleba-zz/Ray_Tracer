#ifndef LIGHT_H_
#define LIGHT_H_

#include "Vector.hpp"
#include "Color.hpp"

class Light {

  private:
    Vector *position;
    // optionally we can have a non-white colour
    Color *color;

  public:
    Light(Vector *position);
    Light(Vector *position, Color *color);
    ~Light();

};

#endif
