#include "Scene.hpp"

Scene::Scene(const char* file){
  // Reads the number of instances and the feature dimension
  // from the input file

  num_spheres = 0;
  num_sources = 0;
  FILE* f = fopen(file, "r");
  if (f ==  NULL) {
    fprintf(stderr, "ERR: Impossible to open %s\n", file);
    throw -1;
  }

  int ret = fscanf(f, "%i %i", &num_spheres, &num_sources);

  for (int instance = 0; instance < num_spheres; ++instance) {

    int red, green, blue;
    float radius, x, y, z;

    // Reads attributes
    ret = fscanf(f, "%f", &radius);
    ret = fscanf(f, "%i %i %i", &red, &green, &blue);
    ret = fscanf(f, "%f %f %f", &x, &y, &z);

    Color *color = new Color(red, green, blue);
    Vector *position = new Vector(x, y, z);

    // Creates an object for the new instance
    Sphere* sphere = new Sphere(position, radius, color);

    spheres.push_back(sphere);
  }

  for (int instance = 0; instance < num_sources; ++instance) {

    int red, green, blue;
    float x, y, z;

    // Reads attributes
    ret = fscanf(f, "%i %i %i", &red, &green, &blue);
    ret = fscanf(f, "%f %f %f", &x, &y, &z);

    Color *color = new Color(red, green, blue);
    Vector *position = new Vector(x, y, z);

    // Creates an object for the new instance
    Light* source = new Light(position, color);

    sources.push_back(source);
  }

  fclose(f);
}

Scene::~Scene(){
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
