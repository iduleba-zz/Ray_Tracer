#ifndef CAMERA_H_
#define CAMERA_H_

#include "Vector.hpp"

class Camera {

  public:
    Camera(Vector position, Vector target);
    Camera(Vector position, Vector target, Vector up, float screen_width, float screen_height);
    ~Camera();
    
    SetScreenDimensions(float screen_width, float screen_height);

    Vector position;
    Vector target;
    Vector up;
    static float screen_width;
    static float screen_height;
};

#endif
