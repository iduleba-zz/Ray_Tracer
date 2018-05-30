#include <iostream>
#include "Vector.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "Ray.hpp"
#include <mpi.h>

using namespace std;

void printHelp(){
  cout <<"Usage: ./rt camera_file spheres_and_sources_file ./output_img.ppm\n" << endl;
  cout <<"camera_file must have the following format:\n" << endl;
  cout <<"width(int) height(int) -> resolution of the camera" << endl;
  cout <<"x(float) y(float) z(float) -> position of the camera" << endl;
  cout <<"x(float) y(float) z(float) -> position of the target" << endl;
  cout <<"x(float) y(float) z(float) -> upward direction\n" << endl;
  cout <<"spheres_and_sources_file must have the following format:\n" << endl;
  cout <<"Red(0-255) Green(0-255) Blue(0-255) -> Background color" << endl;
  cout <<"number_of_spheres(int) number_ of_sources(int)\n" << endl;
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

int ReadFiles(int rank, int argc, char* argv[], Camera *cam, Scene *scene, const char* outputImg){
  if(rank==0){
    cout <<"Ray Tracer v1.0.\n" << endl;
    if (argc != 4){
      printHelp();
      return -1;
    }
  }

  const char* camera_file = argv[1];
  const char* spheres_and_sources_file = argv[2];
  outputImg = argv[3];

  if(rank==0) cout <<"Extracting camera from " << camera_file << endl;

  try{
      cam = new Camera(camera_file);
  }catch (int e){
    if(rank==0){
      cout << "File \""<< camera_file <<"\" not found!\n" << endl;
      printHelp();
      return -1;
    }
  }

  if(rank==0) cout <<"...Done" << endl;

  if(rank==0) cout <<"Extracting spheres and light sources from " << spheres_and_sources_file << endl;

  try{
    scene = new Scene(spheres_and_sources_file);
  }catch (int e){
    if(rank==0){
      cout << "File \""<< spheres_and_sources_file <<"\" not found!\n" << endl;
      printHelp();
    }
    return -1;
  }

  if(rank==0) cout <<"...Done" << endl;
  return 0;
}

void Chunk(int rank, int size, int length, int *starting_point, int *chunk){

  *starting_point = (length / size) * rank;

  if(rank != size-1)
    *chunk = (length / size);
  else
    *chunk = (length / size) + (length % size);
}

void RenderImage(int rank, int size, Camera *cam, Scene *scene, Image *img){

  int start=0, chunk=0;
  Chunk(rank, size, cam->ScreenWidth() * cam->ScreenHeight(), &start, &chunk);

  cout <<"Process "<<rank+1<<"/"<<size<<": Rendering Image from " << start <<" to "<< start+chunk << endl;
  img = cam->Render(scene, start, chunk);

  cout <<"Process "<<rank+1<<"/"<<size<<": Rendering Done" << endl;
}

void JoiningResults(int rank, int size, Image *img){
  //communicate the results back to root
  if(rank == 0){
    cout <<"Process "<<rank+1<<"/"<<size<<": Receiving Partial Images"<< endl;
    for(int i = 1; i < size; i++){
      unsigned int* unrolledImage = new unsigned int[img->ImageWidth()*img->ImageHeight()];
      MPI_Recv(unrolledImage, img->ImageWidth()*img->ImageHeight(), MPI_UNSIGNED, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      delete[] unrolledImage;
      cout <<"Process "<<rank+1<<"/"<<size<<": Received from Process "<<i+1<<"/"<<size<< endl;
    }
  }
  else{
    cout <<"Process "<<rank+1<<"/"<<size<<": Sending Partial Image to Root"<< endl;
    unsigned int* unrolledImage = img->ToArray();
    MPI_Send(unrolledImage, img->ImageWidth()*img->ImageHeight(), MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD);
    delete[] unrolledImage;
  }
  cout <<"Process "<<rank+1<<"/"<<size<<": Done" << endl;
}

void ExportingImage(int rank, Image *img, const char* outputImg){
    if(rank==0){
      cout <<"Exporting image to " << outputImg << endl;
      img->ExportPPM(outputImg);//"./untitled1.ppm"
    }
    cout <<"...Done" << endl;
}

int main(int argc, char* argv[]) {
  MPI_Init(&argc, &argv);
  int rank, size;
  MPI_Status status;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  Camera *cam; Scene *scene; Image* img; const char* outputImg;

  //all processes read the files
  //if(ReadFiles(rank, argc, argv, cam, scene, outputImg)!=0) return -1;

  if(rank==0){
    cout <<"Ray Tracer v1.0.\n" << endl;
    if (argc != 4){
      printHelp();
      return -1;
    }
  }

  const char* camera_file = argv[1];
  const char* spheres_and_sources_file = argv[2];
  outputImg = argv[3];

  if(rank==0) cout <<"Process "<<rank+1<<"/"<<size<<": Extracting camera from " << camera_file << endl;

  try{
      cam = new Camera(camera_file);
  }catch (int e){
    if(rank==0){
      cout << "File \""<< camera_file <<"\" not found!\n" << endl;
      printHelp();
      return -1;
    }
  }

  if(rank==0) cout <<"Process "<<rank+1<<"/"<<size<<": ...Done" << endl;

  if(rank==0) cout <<"Process "<<rank+1<<"/"<<size<<": Extracting spheres and light sources from " << spheres_and_sources_file << endl;

  try{
    scene = new Scene(spheres_and_sources_file);
  }catch (int e){
    if(rank==0){
      cout << "File \""<< spheres_and_sources_file <<"\" not found!\n" << endl;
      printHelp();
      return -1;
    }
  }

  if(rank==0) cout <<"Process "<<rank+1<<"/"<<size<<" ...Done" << endl;

  //RenderImage(rank, size, cam, scene, img);
  int start=0, chunk=0;
  Chunk(rank, size, cam->ScreenWidth() * cam->ScreenHeight(), &start, &chunk);

  cout <<"Process "<<rank+1<<"/"<<size<<": Rendering Image from " << start <<" to "<< start+chunk << endl;
  img = cam->Render(scene, start, chunk);

  cout <<"Process "<<rank+1<<"/"<<size<<": Rendering Done" << endl;

  //JoiningResults(rank, size, img);
  //communicate the results back to root
  if(rank == 0){
    cout <<"Process "<<rank+1<<"/"<<size<<": Receiving Partial Images"<< endl;
    for(int i = 1; i < size; i++){
      unsigned int* unrolledImage = new unsigned int[3*img->ImageWidth()*img->ImageHeight()];
      MPI_Recv(unrolledImage, 3*img->ImageWidth()*img->ImageHeight(), MPI_UNSIGNED, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      Image img2 = (*img) + Image(img->ImageWidth(), img->ImageHeight(), unrolledImage);
      delete img;
      img = new Image(img2);
      delete[] unrolledImage;
      cout <<"Process "<<rank+1<<"/"<<size<<": Received from Process "<<i+1<<"/"<<size<< endl;
    }
  }
  else{
    cout <<"Process "<<rank+1<<"/"<<size<<": Sending Partial Image to Root"<< endl;
    unsigned int* unrolledImage = img->ToArray();
    MPI_Send(unrolledImage, 3*img->ImageWidth()*img->ImageHeight(), MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD);
    delete[] unrolledImage;
  }
  cout <<"Process "<<rank+1<<"/"<<size<<": Done" << endl;

  //ExportingImage(rank, img, outputImg);
  if(rank==0){
    cout <<"Process "<<rank+1<<"/"<<size<<": Exporting image to " << outputImg << endl;
    cout <<"...Done" << endl;
  }

  //clean
  delete scene;
  delete cam;
  delete img;

  MPI_Finalize();

  if(rank==0) cout << "Exited Successfully!" << endl;
  return 0;
}


/*
TODO list:
29/05
4 e 5
olhar a precisao 0.001???
*/
