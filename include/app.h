#ifndef APP_H
#define APP_H

#include "ray_caster.h"


static const char* WINDOW_TITLE = "Sphere";
static const SDL_Rect RENDERER_DEFAULT_LOCATION = {
  0,
  0,
  WINDOW_WIDTH,
  WINDOW_HEIGHT
};


class App {
  SDL_Window* window;
  SDL_Renderer* renderer;

  enum State {
    OK,
    SDL_ERR
  };

  State state;
 public:
  App();

  ~App();

  void ClearScreen();

  State ReportState() const;

  void Exec();
};


#endif /* app.h */
