#include <iostream>
#include "Vector.hpp"
#include "Camera.hpp"
#include "Color.hpp"
#include "Light.hpp"
#include "Scene.hpp"
#include "Ray.hpp"

using namespace std;

int main(int argc, char* argv[]) {
  Scene *scene = new Scene("Spheres.in");
  Ray *ray = new Ray(Vector(0,0,0),Vector(0,5,1));
  float t1,t2;
  cout << ray->Intersects(scene->Spheres()[0],&t1,&t2) << endl;
  cout << "t1 = " << t1 << ", t2 = " << t2 << endl;
  Camera *cam = new Camera(new Vector(0,0,-10),new Vector(0,0,0),new Vector(1,0,0));
  Color** color = cam->Render(scene, NULL);
  cam->ExportPPM(color, "./untitled1.ppm");
  return 0;
}


/*
TODO list:
28/05
Pegar a esfera mais proxima!
Adiciona um role q quando ta dentro da esfera t1 tem q ser o raio certo
2.2, 3, 4 e 5
*/
