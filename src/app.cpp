#include "app.h"


App::App() {
  if (SDL_Init(SDL_INIT_EVERYTHING)) {
    state = APP_SDL_ERR;
    ReportState();
    return;
  }

  window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  if (!window) {
    state = APP_SDL_ERR;
    ReportState();
    return;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    state = APP_SDL_ERR;
    ReportState();
    return;
  }
}

App::~App() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}


void App::ClearScreen() {
  SDL_SetRenderTarget(renderer, NULL);
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
  SDL_RenderClear(renderer);
}


AppState App::ReportState() const {
  fprintf(stderr, "App reports: ");
  switch (state) {
    case APP_OK:
      fprintf(stderr, "ok\n");
      break;
    case APP_SDL_ERR:
      fprintf(stderr, "SDL error. SDL reports: %s\n", SDL_GetError());
      break;
    default:
      fprintf(stderr, "unexpected state\n");
      break;
  }
  fflush(stderr);
  return state;
}


void App::Exec() {
  double upp = 1;
  RayCaster ray_caster(renderer);
  Camera camera(Vector(800, 400, 300), Vector(-1, 0, 0));
  Lighter ligher(Vector(0, 0, 600), ColorRGB(0.8, 0.8, 0.8));
  ColorRGB ambient(0.15, 0.15, 0.15);
  Sphere sphere(Vector(-800, 400, 300), 500, ColorRGB(1, 0, 0.2), 32);
  World world(ligher, sphere, ambient, camera);

  bool is_open = true;
  SDL_Event event;
  while (is_open) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          is_open = false;
          break;
        default:
          break;
      }
    }
    if (!is_open)
      break;

    time_t prev_t = SDL_GetTicks();
    ClearScreen();
    ray_caster.RenderWorld(world, upp);
    SDL_RenderPresent(renderer);
    time_t cur_t = SDL_GetTicks();
    printf("[FPS]: %lf\n", 1000.0f / (cur_t - prev_t));
  }
}
