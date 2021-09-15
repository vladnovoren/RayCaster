#include "app.h"


App::App() {
  if (SDL_Init(SDL_INIT_EVERYTHING)) {
    state = SDL_ERR;
    ReportState();
    return;
  }

  window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  if (!window) {
    state = SDL_ERR;
    ReportState();
    return;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    state = SDL_ERR;
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


App::State App::ReportState() const {
  fprintf(stderr, "App reports: ");
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


void App::Exec() {
  double upp = 1;
  RayCaster ray_caster(renderer);
  Camera camera(Vector(800, 400, 300), Vector(-1, 0, 0));
  Lighter ligher(Vector(0, 0, 600), ColorRGB(0.75, 0.75, 0.75));
  ColorRGB ambient(0.15, 0.15, 0.15);
  Sphere sphere(Vector(-800, 400, 300), 300, ColorRGB(1, 0.2, 0.6), 32);
  World world(ligher, sphere, ambient, camera);

  ButtonsHandler buttons(renderer);
  Button cam_forward({380, 510, 40, 40}, ColorRGB(255, 0, 0));
  Button cam_back({380, 560, 40, 40}, ColorRGB(255, 0, 0));
  Button cam_right({430, 560, 40, 40}, ColorRGB(255, 0, 0));
  Button cam_left({330, 560, 40, 40}, ColorRGB(255, 0, 0));
  Button change_material({480, 560, 40, 40}, ColorRGB(255, 0, 0));
  Button change_color({280, 560, 40, 40}, ColorRGB(255, 0, 0));

  size_t cam_forward_id = buttons.AddButton(cam_forward);
  size_t cam_back_id = buttons.AddButton(cam_back);
  size_t cam_right_id = buttons.AddButton(cam_right);
  size_t cam_left_id = buttons.AddButton(cam_left);
  size_t change_material_id = buttons.AddButton(change_material);
  size_t change_color_id = buttons.AddButton(change_color);

  bool is_open = true;
  SDL_Event event;
  while (is_open) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          is_open = false;
          break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
          buttons.HandleEvent(event.button);
          break;
        default:
          break;
      }
    }
    if (!is_open)
      break;

    if (buttons.GetButtonState(cam_forward_id) == Button::PRESSED)
      world.camera.pos += Vector(-10, 0, 0);
    
    if (buttons.GetButtonState(cam_back_id) == Button::PRESSED)
      world.camera.pos += Vector(10, 0, 0);

    if (buttons.GetButtonState(cam_right_id) == Button::PRESSED)
      world.camera.pos += Vector(0, 10, 0);
    
    if (buttons.GetButtonState(cam_left_id) == Button::PRESSED)
      world.camera.pos += Vector(0, -10, 0);
    
    if (buttons.GetButtonState(change_material_id) == Button::PRESSED) {
      world.sphere.material++;
      world.sphere.material %= 32;
    }

    if (buttons.GetButtonState(change_color_id) == Button::PRESSED) {
      world.sphere.color.r = (double)(rand() % 100) / 200 + 0.1;
      world.sphere.color.g = (double)(rand() % 100) / 200 + 0.1;
      world.sphere.color.b = (double)(rand() % 100) / 200 + 0.1;
    }

    ClearScreen();

    ray_caster.RenderWorld(world, upp);
    buttons.RenderButtons();
    SDL_RenderPresent(renderer);
  }
}
