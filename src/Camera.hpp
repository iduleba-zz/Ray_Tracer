#ifndef CAMERA_H_
#define CAMERA_H_

#include "Vector.hpp"
#include "Color.hpp"
#include "Image.hpp"
#include "Scene.hpp"
#include "Ray.hpp"
#include <vector>
#include <math.h>

class Camera{

  private:
    int width;
    int height;

    Vector *position;
    Vector *target;
    Vector *up;

    //RayTracer
    Color* RayTrace(Scene *scene, Ray ray);

    Color* PhongReflection(Sphere *sphere, Vector point, Scene* scene);

  public:
    Camera(Vector *position, Vector *target);
    Camera(Vector *position, Vector *target, Vector *up);
    Camera(Vector *position, Vector *target, Vector *up, int width, int height);
    ~Camera();

    int ScreenWidth() const { return Camera::width; };
    int ScreenHeight() const { return Camera::height; };
    void SetScreenDimensions (int width, int height);

    Vector *Position() const { return position; };
    Vector *Target() const { return target; };
    Vector *Up() const { return up; };

    //compute the image
    Image* Render(Scene *scene);

};

#endif
