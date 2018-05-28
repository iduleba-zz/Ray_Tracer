#include "Camera.hpp"
#include <fstream>
#include <vector>
#include <math.h>

int Camera::width = 800;
int Camera::height = 600;

Camera::Camera(Vector *position, Vector *target) : Camera(position, target, new Vector(0,0,1)) {}

Camera::Camera(Vector *position, Vector *target, Vector *up) {
  this->position = position;
  this->target = target;
  this->up = up;
  this->up->Normalize();
}

Camera::~Camera(){
  delete position;
  delete target;
  delete up;
}

Camera::Camera(Vector *position, Vector *target, Vector *up, int width, int height) : Camera(position, target, up){
  SetScreenDimensions(width, height);
}

void Camera::SetScreenDimensions(int width, int height){
  Camera::width = width;
  Camera::height = height;
}

Color* Camera::RayTrace(Scene *scene, Ray ray, Light *light){
  std::vector<Sphere*> spheres = scene->Spheres();
  for(int i=0; i<scene->NumSpheres(); i++){
    float t1, t2;
    bool ret = ray.Intersects(spheres[i], &t1, &t2);
    if (ret==true){
      //std::cout << "Yes!" << spheres[i]->Color_()->Red() << std::endl;
      return new Color(spheres[i]->Color_());
    }else{
      std::cout << "No!" << spheres[i]->Color_()->Red() << std::endl;
      return new Color(128,128,0);
    }
  }
}

Color** Camera::Render(Scene *scene, Light *light){
  Color **image = new Color*[width * height];

  float invWidth = 1 / float(width), invHeight = 1 / float(height);
  float fov = 30, aspectratio = width / float(height);
  float angle = tan(M_PI * 0.5 * fov / 180.);

  Vector foward = (*target - *position);
  std::cout << "Up: " << up->x << up->y << up->z << std::endl;
  std::cout << "Fow: " << foward.x << foward.y << foward.z << std::endl;
  foward.Normalize();
  std::cout << "Fow N: " << foward.x << foward.y << foward.z << std::endl;
  Vector right = (*up) ^ foward;
  std::cout << "right: " << right.x << right.y << right.z << std::endl;

  //Ray Tracing
  int count = 0;
  for (unsigned y = 0; y < height; ++y) {
    for (unsigned x = 0; x < width; ++x, ++count) {
      //create ray from eye to pixel[x][y]

      float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
      float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;

      Vector direction = foward + (*up)*xx+ right*yy;
      direction.Normalize();
      Ray ray = Ray(*position, direction);

      //std::cout << direction.x << direction.y << direction.z << std::endl;
      //RayTracer algorithm
      image[count] = RayTrace(scene, ray, light);
    }
  }
  return image;
}


void Camera::ExportPPM(Color ** image, const char* fileName){
  // Save PPM image
  //fileName should be like "./untitled.ppm"
  std::ofstream ofs(fileName, std::ios::out | std::ios::binary);
  ofs << "P6\n" << width << " " << height << "\n255\n";
  for (unsigned i = 0; i < width * height; ++i) {
    //if(image[i]->Red() == 128)
      //std::cout << image[i]->Red() << "," << image[i]->Green() << "," <<image[i]->Blue() << std::endl;
    ofs << (unsigned char) image[i]->Red() << (unsigned char) image[i]->Green() << (unsigned char) image[i]->Blue();
  }
  ofs.close();
}
