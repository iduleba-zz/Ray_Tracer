#ifndef SCENE_H_
#define SCENE_H_

#include "Vector.hpp"
#include "Sphere.hpp"
#include <vector>
#include <iostream>

using namespace std;

class Scene {

  private:
    //set of spheres
    std::vector<Sphere*> spheres;
    int num_spheres;

  public:
    Scene(const char* file);
    ~Scene();
    int NumSpheres(){ return num_spheres;};
    std::vector<Sphere*> Spheres() { return spheres;};
};

#endif
