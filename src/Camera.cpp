#include "Camera.hpp"

Camera::Camera(Vector *position, Vector *target) : Camera(position, target, new Vector(0,0,1)) {}

Camera::Camera(Vector *position, Vector *target, Vector *up) {
  this->width = 800;
  this->height = 600;
  this->position = position;
  this->target = target;
  this->up = up;
  this->up->Normalize();
}

Camera::Camera(Vector *position, Vector *target, Vector *up, int width, int height) : Camera(position, target, up){
  SetScreenDimensions(width, height);
}

Camera::~Camera(){
  delete position;
  delete target;
  delete up;
}

void Camera::SetScreenDimensions(int width, int height){
  this->width = width;
  this->height = height;
}

Color* Camera::RayTrace(Scene *scene, Ray ray){
  std::vector<Sphere*> spheres = scene->Spheres();
  float t_min = -1;
  int sphere_index;
  for(int i=0; i<scene->NumSpheres(); i++){
    float t1, t2;
    bool ret = ray.Intersects(spheres[i], &t1, &t2);
    if (ret==true){
      if(t1 < t_min || t_min == -1){
        sphere_index = i;
        t_min = t1;
      }
      //std::cout << "Yes!" << spheres[i]->Color_()->Red() << std::endl;
    }else{
      //std::cout << "No!" << spheres[i]->Color_()->Red() << std::endl;

    }
  }
  if(t_min >= 0)
    return new Color(spheres[sphere_index]->Color_());
  else
    return new Color(50,200,100);
}

Image* Camera::Render(Scene *scene){
  //Color **image = new Color*[width * height];
  Image *image = new Image(width, height);

  //coping with the geometry
  float invWidth = 1 / float(width), invHeight = 1 / float(height);
  float fov = 30, aspectratio = width / float(height);
  float angle = tan(M_PI * 0.5 * fov / 180.);

  //define a few vectors to simplify notation
  Vector foward = (*target - *position);
  //std::cout << "Up: " << up->x << up->y << up->z << std::endl;
  //std::cout << "Fow: " << foward.x << foward.y << foward.z << std::endl;
  foward.Normalize();
  //std::cout << "Fow N: " << foward.x << foward.y << foward.z << std::endl;
  Vector right = (*up) ^ foward;
  //std::cout << "right: " << right.x << right.y << right.z << std::endl;

  //Ray Tracing
  int count = 0;
  for (unsigned y = 0; y < height; ++y) {
    for (unsigned x = 0; x < width; ++x, ++count) {
      //scaling factors
      float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
      float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;

      Vector direction = foward + (*up)*xx+ right*yy;
      direction.Normalize();

      //create ray from eye to pixel[x][y]
      Ray ray = Ray(*position, direction);

      //std::cout << direction.x << direction.y << direction.z << std::endl;
      //Call to the RayTracer algorithm
      try{
        image->ImageSet(count, RayTrace(scene, ray));
      }catch(int e){
        std::cout << "Out of bounds! Index: " << count << std::endl;
      }
    }
  }
  return image;
}
