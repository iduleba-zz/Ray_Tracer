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
    if (ray.Intersects(spheres[i], &t1, &t2)==true && (t1 < t_min || t_min == -1)){
      sphere_index = i;
      t_min = t1;
    }
  }
  if(t_min >= 0)
    //provisorio. Adicionar Phong
    //return new Color(spheres[sphere_index]->Color_());
    return PhongReflection(spheres[sphere_index], ray.Position() + ray.Direction() * t_min, scene );
  else
    return new Color(50,200,100);
}

Image* Camera::Render(Scene *scene){
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

Color* Camera::PhongReflection(Sphere *sphere, Vector point, Scene* scene){

  Vector normal = *(sphere->Normal(point));

  vector<Light*> sources = scene->Sources();


  vector<Vector> reflected_rays, source_rays;
  for(int i = 0; i < scene->NumSources(); i++){
    //direction vectors from the point on the surface toward each light source
    Vector point_to_source = (*(sources[i]->Position()) - point);
    point_to_source.Normalize();
    source_rays.push_back(point_to_source);

    // direction vectors representing the reflected rays from each light source
    Vector proj = normal * (normal * source_rays[i]);
    reflected_rays.push_back(proj * 2 - source_rays[i]);
  }

  // direction vector from the sphere point towards the camera
  Vector point_to_camera = *(this->position) - point;
  point_to_camera.Normalize();

  // Calculation of the ambient, diffuse and specular light
  Color ambient_light = Color(0,0,0);
  Color diffuse_light = Color(0,0,0);
  Color specular_light = Color(0,0,0);
  for(int i = 0; i < scene->NumSources(); i++){
    ambient_light += *(sources[i]->AmbientColor()) * sphere->ReflectionConstants()[AMBIENT];
    float dot = point_to_camera * reflected_rays[i];
    specular_light += (dot > 0) ? (*(sources[i]->DiffuseColor())) * sphere->ReflectionConstants()[SPECULAR] * pow( point_to_camera * reflected_rays[i], sphere->ReflectionConstants()[SHININESS] ) : 0;
    diffuse_light += (*(sources[i]->SpecularColor())) * sphere->ReflectionConstants()[DIFFUSE] * ( normal * source_rays[i] );
  }

  return new Color(ambient_light + diffuse_light + specular_light);

}
