#ifndef SCENE_H_
#define SCENE_H_

#include "Vector.hpp"
#include "Sphere.hpp"
#include "Light.hpp"
#include <vector>
#include <iostream>
#include <stdio.h>

using namespace std;

class Scene {

  private:
    //set of spheres
    std::vector<Sphere*> spheres;
    int num_spheres;
    std::vector<Light*> sources;
    int num_sources;
    Color* background_color;
  public:
    Scene(const char* file);
    ~Scene();
    int NumSpheres() const { return num_spheres;};
    int NumSources() const { return num_sources;};
    std::vector<Sphere*> Spheres() const { return spheres;};
    std::vector<Light*> Sources() const { return sources;};
    Color* BackgroundColor();
};

#endif
