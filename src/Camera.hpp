#ifndef CAMERA_H_
#define CAMERA_H_

#include "Vector.hpp"

class Camera {

  public:
    Vector position;
    Vector target;
    Vector up;
    float screen_width;
    float screen_height;


};

#endif
