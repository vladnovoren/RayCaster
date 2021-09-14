#include "ray_caster.h"


// Screen
//==============================================================================
Screen::Screen() {
}


Screen::Screen(const Vector& pos, const Vector& px_vec, const Vector& py_vec) {
  this->pos = pos;
  this->px_vec = px_vec;
  this->py_vec = py_vec;
}


void Screen::Prepare(const Camera& camera, double upp) {
  px_vec = camera.dir ^ Vector(0, 0, 1);
  px_vec.Resize(upp);

  py_vec = camera.dir ^ px_vec;
  py_vec.Resize(upp);

  pos = camera.pos + WINDOW_WIDTH * camera.dir - (WINDOW_WIDTH / 2) * px_vec - (WINDOW_HEIGHT / 2) * py_vec;
}
//==============================================================================


// RayCaster
//==============================================================================
RayCaster::RayCaster () {
}


RayCaster::RayCaster(SDL_Renderer* renderer) {
  this->renderer = renderer;
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
  if (!texture) {
    state = SDL_ERR;
    ReportState();
    return;
  }
}


RayCaster::~RayCaster() {
  SDL_DestroyTexture(texture);
}


RayCaster::State RayCaster::ReportState() const {
  fprintf(stderr, "RayCaster reports: ");
  switch (state) {
    case OK:
      fprintf(stderr, "ok\n");
      break;
    case SDL_ERR:
      fprintf(stderr, "SDL error. SDL reports: %s\n", SDL_GetError());
      break;
    default:
      fprintf(stderr, "unexpected state\n");
      break;
  }
  fflush(stderr);
  return state;
}


void RayCaster::RenderWorld(const World& world, double upp) {
  screen.Prepare(world.camera, upp);
  SDL_SetRenderTarget(renderer, texture);
  RenderSphere(world);
  SDL_SetRenderTarget(renderer, NULL);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
}


Vector RayCaster::PixelToReal(int px, int py) {
  return screen.pos + px * screen.px_vec + py * screen.py_vec;
}


void RayCaster::RenderSphere(const World& world) {
  for (int py = 0; py < WINDOW_HEIGHT; ++py) {
    for (int px = 0; px < WINDOW_WIDTH; ++px) {
      ColorRGB color = GetSpherePixelColor(world, px, py);
      SDL_SetRenderDrawColor(renderer, (int)color.r, (int)color.g, (int)color.b, 0xff);
      SDL_RenderDrawPoint(renderer, px, py);
    }
  }
}


ColorRGB RayCaster::GetSpherePixelColor(const World& world, int px, int py) {
  Vector dir = PixelToReal(px, py) - world.camera.pos;
  Vector intersec;
  int is_intersec = VectorSphereIntersec(world.sphere, world.camera.pos, dir, &intersec);
  if (!is_intersec)
    return ColorRGB(0, 0, 0);

  Vector normal = intersec - world.sphere.center;
  normal.Normalize();
  Vector r_light_dir = world.lighter.pos - intersec;
  r_light_dir.Normalize();
  Vector reflected = r_light_dir;
  reflected.Reflect(normal);
  reflected.Normalize();
  Vector to_camera = world.camera.pos - intersec;
  to_camera.Normalize();

  ColorRGB result;
  ColorRGB diffuse = GetDiffuse(world.lighter, r_light_dir, normal);
  ColorRGB specular = GetSpecular(world.lighter.color, reflected, to_camera, world.sphere.material);
  result = world.sphere.color * (diffuse + world.ambient) + specular;
  result.Format();
  return result;
}


ColorRGB RayCaster::GetDiffuse(const Lighter& lighter, const Vector& r_light_dir, const Vector& normal) {
  ColorRGB diffuse = lighter.color;
  diffuse *= Max(0, r_light_dir * normal);
  return diffuse;
}


ColorRGB RayCaster::GetSpecular(const ColorRGB& light_color, const Vector& reflected, const Vector& to_camera, int material) {
  ColorRGB specular = light_color;
  specular *= pow(Max(reflected * to_camera, 0), material);
  return specular;
}
//==============================================================================
