#include <iostream>
#include "Vector.hpp"
#include "Scene.hpp"
#include "Ray.hpp"

using namespace std;

int main(int argc, char* argv[]) {
  Scene *scene = new Scene("Spheres.in");
  Ray *ray = new Ray(new Vector(0,0,0),new Vector(0,0,1));
  printf("%d", ray->Intersects(scene->Spheres()[0]));
  return 0;
}


/*
TODO list:
27/05
testar interseccao de ray com sphere!

*/
