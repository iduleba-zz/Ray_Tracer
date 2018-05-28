#ifndef CAMERA_H_
#define CAMERA_H_

#include "Vector.hpp"

class Camera {

  private:
    static int screen_width;
    static int screen_height;

    Vector *position;
    Vector *target;
    Vector *up;

  public:
    Camera(Vector *position, Vector *target);
    Camera(Vector *position, Vector *target, Vector *up, int screen_width, int screen_height);
    ~Camera();

    static float ScreenWidth() const { return Camera::screen_width; };
    static float ScreenHeight() const { return Camera::screen_height; };
    static SetScreenDimensions(float screen_width, float screen_height);

    Vector *Position() const { return position; };
    Vector *Target() const { return target; };
    Vector *Up() const { return up; };

};

#endif
