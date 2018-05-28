#include <iostream>
#include "Vector.hpp"
#include "Scene.hpp"
#include "Ray.hpp"

using namespace std;

int main(int argc, char* argv[]) {
  Scene *scene = new Scene("Spheres.in");
  Ray *ray = new Ray(Vector(0,0,0),Vector(0,0,1));
  float t1,t2;
  cout << ray->Intersects(scene->Spheres()[0],&t1,&t2) << endl;
  cout << "t1 = " << t1 << ", t2 = " << t2 << endl;
  return 0;
}


/*
TODO list:
27/05
testar interseccao de ray com sphere!

*/
