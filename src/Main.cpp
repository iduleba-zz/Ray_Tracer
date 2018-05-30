#include <iostream>
#include "Vector.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "Ray.hpp"
//#include <mpi.h>

using namespace std;

void printHelp(){
  cout <<"Usage: ./rt camera_file spheres_file ./output_img.ppm\n" << endl;
  cout <<"camera_file must have the following format:\n" << endl;
  cout <<"width(int) height(int) -> resolution of the camera" << endl;
  cout <<"x(float) y(float) z(float) -> position of the camera" << endl;
  cout <<"x(float) y(float) z(float) -> position of the target" << endl;
  cout <<"x(float) y(float) z(float) -> upward direction\n" << endl;
  cout <<"spheres_file must have the following format:\n" << endl;
  cout <<"The first line contains the number of spheres and the number of sources in the file.\n" << endl;
  cout <<"For each sphere, four lines will be read:" << endl;
  cout <<"radius(float)" << endl;
  cout <<"ka(float) kd(float) ks(float) sh(float) refl(float) -> reflection parameters" << endl;
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

  if (argc != 4){
    printHelp();
    return -1;
  }

  const char* camera_file = argv[1];
  const char* spheres_and_sources_file = argv[2];
  const char* outputImg = argv[3];

  cout <<"Extracting camera from " << camera_file << endl;
  Camera *cam;
  try{
      cam = new Camera(camera_file);
  }catch (int e){
    cout << "File \""<< camera_file <<"\" not found!\n" << endl;
    printHelp();
    return -1;
  }

  cout <<"...Done" << endl;

  cout <<"Extracting spheres and light sources from " << spheres_and_sources_file << endl;
  Scene *scene;
  try{
    scene = new Scene(spheres_and_sources_file);
  }catch (int e){
    cout << "File \""<< spheres_and_sources_file <<"\" not found!\n" << endl;
    printHelp();
    return -1;
  }

  cout <<"...Done" << endl;
  cout <<"Rendering Image"<< endl;

  //test image
  Image* img = cam->Render(scene);

  cout <<"...Done" << endl;

  cout <<"Exporting image to " << outputImg << endl;
  img->ExportPPM(outputImg);//"./untitled1.ppm"

  cout <<"...Done" << endl;
  cout << "Terminating" << endl;

  //clean
  delete scene;
  delete cam;
  delete img;

  return 0;
}


/*
TODO list:
29/05
4 e 5
olhar a precisao 0.001???
*/
