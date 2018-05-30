#include "Camera.hpp"

Camera::Camera(const char* file){

  width = 800;
  height = 600;

  FILE* f = fopen(file, "r");
  if (f ==  NULL) {
    fprintf(stderr, "ERR: Impossible to open %s\n", file);
    throw -2;
  }

  int ret = fscanf(f, "%i %i", &width, &height);

  float x, y, z;

  // Reads attributes
  ret = fscanf(f, "%f %f %f", &x, &y, &z);
  position = new Vector(x, y, z);
  ret = fscanf(f, "%f %f %f", &x, &y, &z);
  target = new Vector(x, y, z);
  ret = fscanf(f, "%f %f %f", &x, &y, &z);
  up = new Vector(x, y, z);

  fclose(f);
}

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

// Returns the first sphere reached by the ray.
// t_min represents the parametrized index of the ray where the first intersection occurs. Default value is -1 if no sphere is found.
// the sphere parameter determines if the method should ignore a particular sphere, i.e., if the ray leaves such sphere
Sphere* Camera::ClosestSphere(Scene *scene, Ray ray, float *t_min, Sphere* sphere){
  *(t_min) = -1;
  int sphere_index;
  for(int i=0; i<scene->NumSpheres(); i++){
    float t1, t2;
    if (ray.Intersects(scene->Spheres()[i], &t1, &t2)==true && (t1 < *(t_min) || *(t_min) == -1) && scene->Spheres()[i] != sphere){
      sphere_index = i;
      *(t_min) = t1;
    }
  }
  if(*(t_min) >= 0)
    return scene->Spheres()[sphere_index];
  else
    return nullptr;
}

Color* Camera::RayTrace(Scene *scene, Ray ray){
  std::vector<Sphere*> spheres = scene->Spheres();

  // Calculation of the closest sphere
  float t_min;
  Sphere* closest_sphere = ClosestSphere(scene, ray, &t_min, nullptr);

  if(t_min >= 0){
    //Color *illumination = PhongReflection(closest_sphere, ray.Position() + ray.Direction() * t_min, scene );
    //*illumination = *illumination + mesh_color;
    //return illumination;
    Color illumination = Reflection(closest_sphere, ray.Position() + ray.Direction() * t_min, scene, ray.Direction(), closest_sphere->ReflectionConstants()[REFLECTIVITY]);
    return new Color(illumination);
  }
  else
  //return Background color;
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
        std::cout << "Exception(" << e << ") " << "Out of bounds! Index: " << count << std::endl;
      }
    }
  }
  return image;
}

Color Camera::Reflection(Sphere *sphere, Vector point, Scene* scene, Vector incoming_ray, float r){

  // if intensidade é maior q um delta
  // calcula o raio refletido, que é o espelhado do que chega em relacao a normal.
  // testa se esse raio intersecta uma esfera
  // chama PhongReflection na esfera que o raio intersectou
  // no final faz a conta somando a cor calculada da cor do nego.

  float k = sphere->ReflectionConstants()[REFLECTIVITY]; // material constant representing the "reflectivity"

  Color* c = PhongReflection(sphere, point, scene);
  Color cs = Color(c);
  delete c;

  if(r < 0.0039)
    return (cs);

  //normal vector at the point
  Vector normal = sphere->Normal(point);
  // the projection onto the vector normal to the sphere
  Vector proj = normal * (normal * incoming_ray) * (-1);
  // direction vectors representing the reflected ray
  Vector reflected = proj * 2 + incoming_ray;
  reflected.Normalize();

  // Calculation of the closest sphere
  float t_min;
  Sphere* closest_sphere = ClosestSphere(scene, Ray(point,reflected), &t_min, sphere);

  if(t_min >= 0){
//cout << "t_min = " << t_min << endl;
//cout << "dist-to-sphere" << (point + reflected * t_min - *(closest_sphere->Position())).Magnitude() << endl;
    Color cr = Reflection(closest_sphere, point + reflected * t_min, scene, reflected, r * k);
    return cr * r + (cs) * (1-r);
  }
  else{//does not intersects with another sphere
    return (cs);
  }
}

Color* Camera::PhongReflection(Sphere *sphere, Vector point, Scene* scene){
  vector<Light*> sources = scene->Sources();
  vector<Sphere*> spheres = scene->Spheres();

  //initialize colors of this point
  Color ambient_light = Color(0,0,0);
  Color diffuse_light = Color(0,0,0);
  Color specular_light = Color(0,0,0);

  float* material = sphere->ReflectionConstants();

  //normal vector at the point
  Vector normal = sphere->Normal(point);

  // direction vector from the sphere point towards the camera
  Vector point_to_camera = *(this->position) - point;
  point_to_camera.Normalize();

  //loop through all light sources
  //Calculation of the ambient, diffuse and specular light
  for(int i = 0; i < scene->NumSources(); ++i){
    //direction vectors from the point on the surface toward each light source
    Vector point_to_source = (*(sources[i]->Position()) - point);
    point_to_source.Normalize();
    Ray ray = Ray(point, point_to_source);

    // direction vectors representing the reflected rays from each light source
    Vector proj = normal * (normal * point_to_source);
    Vector reflected = proj * 2 - point_to_source;

    //shadows
    //coefficients will determine the amount of light
    float shadow_ambient=1, shadow_diffuse=1, shadow_specular=1;

    //loop through all spheres. If Ray intersects a sphere, this point will be in the shadow.
    float t;
    ClosestSphere(scene, ray, &t, sphere);
    bool isShadow = (t>0);

    ambient_light += *(sources[i]->AmbientColor()) * material[AMBIENT];
    ambient_light = ambient_light;

    float dot = point_to_camera * reflected;
    specular_light += (dot > 0) ? (*(sources[i]->DiffuseColor())) * material[SPECULAR] * pow( dot, sphere->ReflectionConstants()[SHININESS] ) : Color(0,0,0);
    specular_light = specular_light * !isShadow;

    diffuse_light += (*(sources[i]->SpecularColor())) * material[DIFFUSE] * ( normal * point_to_source );
    diffuse_light = diffuse_light* !isShadow;
  }

  Color mesh_color = Color(sphere->Albedo());
  return new Color(mesh_color + ambient_light + diffuse_light + specular_light);
}
