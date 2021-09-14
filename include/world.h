#ifndef WORLD_H
#define WORLD_H

#include "SDL2/SDL.h"
#include "geometry.h"


struct Camera {
  Vector pos;
  Vector dir;

  Camera();

  Camera(const Vector& pos, const Vector& dir);
};

struct Lighter {
  Vector pos;
  ColorRGB color;

  Lighter();

  Lighter(const Vector& pos, const ColorRGB& color);
};

struct World {
  Lighter lighter;
  Sphere sphere;
  ColorRGB ambient;
  Camera camera;

  World();

  World(const Lighter& lighter, const Sphere& sphere, const ColorRGB& ambient, const Camera& camera);
};


#endif /* world.h */
