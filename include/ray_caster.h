#ifndef RAY_CASTER_H
#define RAY_CASTER_H

#include "world.h"


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;


struct Screen {
  Vector pos;
  Vector px_vec;
  Vector py_vec;

  Screen();

  Screen(const Vector& pos, const Vector& px, const Vector& py);

  void Prepare(const Camera& camera, double upp);
};


class RayCaster {
  SDL_Renderer* renderer;
  SDL_Texture* texture;

  Screen screen;

  enum State {
    OK,
    SDL_ERR
  };

  State state;
public:
  RayCaster();

  RayCaster(SDL_Renderer* renderer);

  ~RayCaster();

  State ReportState() const;

  Vector PixelToReal(int px, int py);

  void RenderSphere(const World& world);

  ColorRGB GetSpherePixelColor(const World& world, int px, int py);

  ColorRGB GetDiffuse(const Lighter& lighter, const Vector& r_light_dir, const Vector& normal);

  ColorRGB GetSpecular(const ColorRGB& light_color, const Vector& reflected, const Vector& to_camera, int material);

  void RenderWorld(const World& world, double upp);
};


#endif /* ray_caster.h */
