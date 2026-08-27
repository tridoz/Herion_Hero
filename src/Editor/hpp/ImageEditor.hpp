#include "Image.hpp"

class ImageEditor {
  private:
    Image* img;
    SDL_Renderer* renderer;

  public:
    ImageEditor();
    auto SetImagePath(const std::string&) -> void;
    auto SetRenderer(SDL_Renderer*) -> void;
    auto DrawImage() -> void;
};