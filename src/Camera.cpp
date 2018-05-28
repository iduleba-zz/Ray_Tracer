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
      return new Color(spheres[i]->Color_());
    }else{
      return new Color(255,255,255);
    }
  }
}

Color** Camera::Render(Scene *scene, Light *light){
  Color **image = new Color*[width * height];
  Color **pixel = image;

  float invWidth = 1 / float(width), invHeight = 1 / float(height);
  float fov = 30, aspectratio = width / float(height);
  float angle = tan(M_PI * 0.5 * fov / 180.);

  //Ray Tracing
  for (unsigned y = 0; y < height; ++y) {
    for (unsigned x = 0; x < width; ++x, ++pixel) {
      //create ray from eye to pixel[x][y]

      float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
      float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;

      Vector foward = (*target - *position);
      foward.Normalize();
      Vector right = (*up) ^ foward;

      Vector direction = foward + (*up)*xx+ right*yy;
      direction.Normalize();
      Ray ray = Ray(*position, direction);

      //RayTracer algorithm
      *pixel = RayTrace(scene, ray, light);
    }
  }
}


void Camera::ExportPPM(Color ** image, const char* fileName){
  // Save PPM image
  //fileName should be like "./untitled.ppm"
  std::ofstream ofs(fileName, std::ios::out | std::ios::binary);
  ofs << "P6\n" << width << " " << height << "\n255\n";
  for (unsigned i = 0; i < width * height; ++i) {
    ofs << image[i]->Red() << image[i]->Green() << image[i]->Blue();
  }
  ofs.close();
}
