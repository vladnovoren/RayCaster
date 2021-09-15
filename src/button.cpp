#include "button.h"


Button::Button() {
}


Button::Button(const SDL_Rect& place, const ColorRGB& color) {
  this->place = place;
  this->color = color;
}


void Button::Press() {
  state = PRESSED;
}


void Button::Release() {
  state = RELEASED;
}


SDL_Rect Button::GetPlace() const {
  return place;
}


Button::State Button::GetState() const {
  return state;
}


bool Button::IsInButton(int x, int y) const {
  return place.x <= x && x - place.x < place.w &&
         place.y <= y && y - place.y < place.h;
}


ButtonsHandler::ButtonsHandler(SDL_Renderer* renderer) {
  this->renderer = renderer;
}


size_t ButtonsHandler::AddButton(const Button& button) {
  buttons[n_buttons] = button;
  return n_buttons++;
}


void ButtonsHandler::HandleEvent(const SDL_MouseButtonEvent& event) {
  if (event.button != SDL_BUTTON_LEFT)
    return;
  for (size_t i = 0; i < n_buttons; ++i) {
    if (buttons[i].IsInButton(event.x, event.y)) {
      switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
          buttons[i].Press();
          break;
        case SDL_MOUSEBUTTONUP:
          buttons[i].Release();
          break;
        default:
          break;
      }
    }
  }
}


Button::State ButtonsHandler::GetButtonState(size_t button_id) {
  return buttons[button_id].GetState();
}


void ButtonsHandler::RenderButtons() {
  SDL_SetRenderTarget(renderer, NULL);
  for (size_t i = 0; i < n_buttons; ++i) {
    double mul = buttons[i].state == Button::PRESSED ? 0.8 : 1;
    SDL_SetRenderDrawColor(renderer, buttons[i].color.r * mul, buttons[i].color.g * mul, buttons[i].color.b * mul, 0xff);
    SDL_RenderFillRect(renderer, &buttons[i].place);
  }
}
