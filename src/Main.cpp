#include <iostream>
#include "Vector.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "Ray.hpp"

using namespace std;

void printHelp(){
  cout <<"Usage: ./rt spheres_file ./output_img.ppm\n" << endl;
  cout <<"The input file must have the following format:\n" << endl;
  cout <<"The first line contains the number of spheres and the number of sources in the file.\n" << endl;
  cout <<"For each sphere, four lines will be read:" << endl;
  cout <<"radius(float)" << endl;
  cout <<"ka(float) kd(float) ks(float) sh(float) -> reflection parameters" << endl;
  cout <<"Red(0-255) Green(0-255) Blue(0-255) -> color of the sphere" << endl;
  cout <<"x(float) y(float) z(float) -> coordinates of the center\n" << endl;
  cout <<"Then, for each source, four lines will be read:" << endl;
  cout <<"Red(0-255) Green(0-255) Blue(0-255) -> ambient component of the light" << endl;
  cout <<"Red(0-255) Green(0-255) Blue(0-255) -> diffuse component of the light" << endl;
  cout <<"Red(0-255) Green(0-255) Blue(0-255) -> specular component of the light" << endl;
  cout <<"x(float) y(float) z(float) -> position of the source\n" << endl;
}

int main(int argc, char* argv[]) {
  cout <<"Ray Tracer v1.0.\n" << endl;

  if (argc != 3){
    printHelp();
    return -1;
  }

  const char* test_file = argv[1];
  const char* outputImg = argv[2];

  Scene *scene;
  try{
    scene = new Scene(test_file);
  }catch (int e){
    cout << "File \""<< argv[1] <<"\" not found!\n" << endl;
    printHelp();
    return -1;
  }

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
2.2, 4 e 5
29/05
Phong model, consider whether the light goes through the same sphere on its way from the source to the point.
*/
