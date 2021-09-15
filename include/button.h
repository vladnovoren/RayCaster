#ifndef BUTTON_H
#define BUTTON_H

#include "color.h"
#include "SDL2/SDL.h"

const size_t MAX_N_BUTTONS = 6;

// class ButtonHandler;

class Button {
public:
  enum State {
    PRESSED,
    RELEASED
  };

  Button();

  Button(const SDL_Rect& place, const ColorRGB& color);

  State GetState() const;

  SDL_Rect GetPlace() const;

  void Press();

  void Release();

  bool IsInButton(int x, int y) const;
private:
  SDL_Rect place;
  ColorRGB color;
  const char* text;
  State state = RELEASED;
  friend class ButtonsHandler;
};



class ButtonsHandler {
  SDL_Renderer* renderer;
  Button buttons[MAX_N_BUTTONS];
  size_t n_buttons = 0;
public:
  ButtonsHandler(SDL_Renderer* renderer);

  size_t AddButton(const Button& button);

  Button::State GetButtonState(size_t button_id);

  void HandleEvent(const SDL_MouseButtonEvent& event);

  void RenderButtons();
};



#endif /* button.h */
