#include "world.h"


Camera::Camera() {
}


Camera::Camera(const Vector& pos, const Vector& dir) {
  this->pos = pos;
  this->dir = dir;
}


Lighter::Lighter() {

}


Lighter::Lighter(const Vector& pos, const ColorRGB& color) {
  this->pos = pos;
  this->color = color;
}


World::World() {

}


World::World(const Lighter& lighter, const Sphere& sphere, const ColorRGB& ambient, const Camera& camera) {
  this->lighter = lighter;
  this->sphere = sphere;
  this->ambient = ambient;
  this->camera = camera;
}

