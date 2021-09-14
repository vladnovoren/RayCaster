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
    state = RAY_CASTER_SDL_ERR;
    ReportState();
    return;
  }
}


RayCaster::~RayCaster() {
  SDL_DestroyTexture(texture);
}


RayCasterState RayCaster::ReportState() const {
  fprintf(stderr, "RayCaster reports: ");
  switch (state) {
    case RAY_CASTER_OK:
      fprintf(stderr, "ok\n");
      break;
    case RAY_CASTER_SDL_ERR:
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
  for (int py = 0; py < WINDOW_HEIGHT; ++py) {
    for (int px = 0; px < WINDOW_WIDTH; ++px) {
      ColorRGB color = GetPixelColor(world, px, py);
      SDL_SetRenderDrawColor(renderer, (int)color.r, (int)color.g, (int)color.b, 0xff);
      SDL_RenderDrawPoint(renderer, px, py);
    }
  }
  SDL_SetRenderTarget(renderer, NULL);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
}


Vector RayCaster::PixelToReal(int px, int py) {
  return screen.pos + px * screen.px_vec + py * screen.py_vec;
}


ColorRGB RayCaster::GetPixelColor(const World& world, int px, int py) {
  Vector dir = PixelToReal(px, py) - world.camera.pos;

  Vector intersec1, intersec2;
  int n_intersecs = GetSphereIntersecs(world.sphere, world.camera.pos, dir, &intersec1, &intersec2);
  if (!n_intersecs || n_intersecs == INF_SOL)
    return ColorRGB(0, 0, 0);
  double len1 = (intersec1 - world.camera.pos).Length();
  double len2 = (intersec2 - world.camera.pos).Length();
  if (!(n_intersecs == 1) && !(len1 < len2))
    intersec1 = intersec2;

  Vector normal = intersec1 - world.sphere.center;
  normal.Normalize();
  Vector r_light_dir = world.lighter.pos - intersec1;

  ColorRGB result;
  ColorRGB diffuse = GetDiffuse(world.lighter, r_light_dir, normal);
  ColorRGB specular = GetSpecular(world.ambient, r_light_dir, normal, intersec1, world.camera.pos, world.sphere.material);
  result = world.sphere.color * (diffuse + world.ambient) + specular;
  result.Format();
  return result;
}


ColorRGB RayCaster::GetDiffuse(const Lighter& lighter, const Vector& r_light_dir, const Vector& normal) {
  ColorRGB diffuse = lighter.color;
  diffuse *= Max(0, VectorsCos(r_light_dir, normal));
  return diffuse;
}


ColorRGB RayCaster::GetSpecular(const ColorRGB& light_color, const Vector& r_light_dir, const Vector& normal, const Vector& intersec, const Vector& camera, int material) {
  ColorRGB specular = light_color;
  Vector reflected = r_light_dir;
  reflected.Reflect(normal);
  double spec_mul = pow(Max(VectorsCos(reflected, camera - intersec), 0), material);
  return specular * spec_mul;
}
//==============================================================================
