#include <iostream>
#include "Vector.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "Ray.hpp"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 3){
    cout <<"Ray Tracer v1.0.\n" << endl;
    cout <<"Usage: ./rt spheres_file output_img.ppm\n" << endl;
    cout <<"The input file must have the following format:\n" << endl;
    cout <<"The first line contains the number of spheres and the number of sources in the file.\n" << endl;
    cout <<"For each sphere, three lines will be read:" << endl;
    cout <<"radius(float)" << endl;
    cout <<"Red(0-255) Green(0-255) Blue(0-255) -> color of the sphere" << endl;
    cout <<"x(float) y(float) z(float) -> coordinates of the center\n" << endl;
    cout <<"For each source, two lines will be read:" << endl;
    cout <<"Red(0-255) Green(0-255) Blue(0-255) -> color of the light" << endl;
    cout <<"x(float) y(float) z(float) -> position of the source\n" << endl;
    return -1;
  }

  const char* test_file = argv[1];
  const char* outputImg = argv[2];

  Scene *scene = new Scene(test_file);

  //test intersection
  Ray *ray = new Ray(Vector(0,0,0),Vector(0,5,1));
  float t1,t2;
  cout << ray->Intersects(scene->Spheres()[0],&t1,&t2) << endl;
  cout << "t1 = " << t1 << ", t2 = " << t2 << endl;

  //test image
  Camera *cam = new Camera(new Vector(0,0,-10),new Vector(0,0,0),new Vector(1,0,0));
  Image* img = cam->Render(scene);
  img->ExportPPM(outputImg);//"./untitled1.ppm"

  //clean
  delete scene;
  delete ray;
  delete cam;
  delete img;

  return 0;
}


/*
TODO list:
28/05
Pegar a esfera mais proxima!
2.2, 3, 4 e 5
29/05
throw exception in ImageSet
throw exception with file not found!
*/
