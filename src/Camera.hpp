#ifndef CAMERA_H_
#define CAMERA_H_

#include "Vector.hpp"
#include "Color.hpp"
#include "Scene.hpp"
#include "Light.hpp"
#include "Ray.hpp"
#include <vector>

class Camera {

  private:
    static int width;
    static int height;

    Vector *position;
    Vector *target;
    Vector *up;

  public:
    Camera(Vector *position, Vector *target);
    Camera(Vector *position, Vector *target, Vector *up);
    Camera(Vector *position, Vector *target, Vector *up, int width, int height);
    ~Camera();

    static float ScreenWidth() { return Camera::width; };
    static float ScreenHeight() { return Camera::height; };
    static void SetScreenDimensions(int width, int height);

    Vector *Position() const { return position; };
    Vector *Target() const { return target; };
    Vector *Up() const { return up; };

    //compute the image
    Color** Render(Scene *scene, Light *light);

    //RayTracer
    Color* RayTrace(Scene *scene, Ray ray, Light *light);

    //print image to a PPM file
    //http://manpages.ubuntu.com/manpages/xenial/man5/ppm.5.html
    void ExportPPM(Color** img, const char* fileName);

};

#endif
