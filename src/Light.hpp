#ifndef LIGHT_H_
#define LIGHT_H_

#include "Vector.hpp"

class Light {

  public:
    Light(Vector position);
    ~Light();
    Vector position;
    // optionally we can have a non-white colour

};

#endif
