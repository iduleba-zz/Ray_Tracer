#ifndef SCENE_H_
#define SCENE_H_

#include "Vector.hpp"
#include "Spheres.hpp"

using namespace std;

class Scene {

  private:
    //set of spheres
    std::vector<Spheres*> spheres;
    int num_spheres;

  public:
    Scene(const char* file);
    ~Scene();
    int NumSpheres(){ return num_spheres;};
    std::vector<Spheres*> Spheres() { return spheres;};
};

#endif
