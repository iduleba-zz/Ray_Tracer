#include "Scene.hpp"
#include "Sphere.hpp"
#include <vector>
#include <iostream>
#include <stdio.h>

Scene::Scene(const char* file){
  // Reads the number of instances and the feature dimension
  // from the input file
  FILE* f = fopen(file, "r");
  if (f ==  NULL) {
    fprintf(stderr, "ERR: Impossible to open %s\n", file);
    return;
  }

  int ret = fscanf(f, "%i", &num_spheres);

  printf("bsdwfuygdfhbwefb %d :",num_spheres);


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
  fclose(f);
}

Scene::~Scene(){
  for (unsigned int i = 0; i < spheres.size(); ++i) {
    delete(spheres[i]);
  }
}
