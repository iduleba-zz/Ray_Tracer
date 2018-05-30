#include "Scene.hpp"

Scene::Scene(const char* file){
  // Reads the from the input file

  num_spheres = 0;
  num_sources = 0;
  FILE* f = fopen(file, "r");
  if (f ==  NULL) {
    fprintf(stderr, "ERR: Impossible to open %s\n", file);
    throw -2;
  }

  int red, green, blue;
  int ret = fscanf(f, "%i %i %i", &red, &green, &blue);
  background_color = new Color(red, green, blue);

  ret = fscanf(f, "%i %i", &num_spheres, &num_sources);

  for (int instance = 0; instance < num_spheres; ++instance) {

    int red, green, blue;
    float radius, x, y, z, ka, kd, ks, sh, refl;

    // Reads attributes
    ret = fscanf(f, "%f", &radius);
    ret = fscanf(f, "%f %f %f %f %f", &ka, &kd, &ks, &sh, &refl);
    ret = fscanf(f, "%i %i %i", &red, &green, &blue);
    ret = fscanf(f, "%f %f %f", &x, &y, &z);

    Color *color = new Color(red, green, blue);
    Vector *position = new Vector(x, y, z);

    // Creates an object for the new instance
    Sphere* sphere = new Sphere(position, radius, color, ka, kd, ks, sh, refl);

    spheres.push_back(sphere);
  }

  for (int instance = 0; instance < num_sources; ++instance) {

    int red_ambient, green_ambient, blue_ambient;
    int red_diffuse, green_diffuse, blue_diffuse;
    int red_specular, green_specular, blue_specular;
    float x, y, z;

    // Reads attributes
    ret = fscanf(f, "%i %i %i", &red_ambient, &green_ambient, &blue_ambient);
    ret = fscanf(f, "%i %i %i", &red_diffuse, &green_diffuse, &blue_diffuse);
    ret = fscanf(f, "%i %i %i", &red_specular, &green_specular, &blue_specular);
    ret = fscanf(f, "%f %f %f", &x, &y, &z);

    Color *color_ambient = new Color(red_ambient, green_ambient, blue_ambient);
    Color *color_diffuse = new Color(red_diffuse, green_diffuse, blue_diffuse);
    Color *color_specular = new Color(red_specular, green_specular, blue_specular);
    Vector *position = new Vector(x, y, z);

    // Creates an object for the new instance
    Light* source = new Light(position, color_ambient, color_diffuse, color_specular);

    sources.push_back(source);
  }

  fclose(f);
}

Color* Scene::BackgroundColor(){
  return background_color;
}

Scene::~Scene(){
  delete background_color;
  if(num_spheres!=0){
    for (unsigned int i = 0; i < spheres.size(); ++i) {
      delete(spheres[i]);
    }
  }
  if(num_sources!=0){
    for (unsigned int i = 0; i < sources.size(); ++i) {
      delete(sources[i]);
    }
  }
}
