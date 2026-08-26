#include "Image.hpp"

class ImageEditor {
  private:
    Image* img;
    SDL_Renderer* renderer;

  public:
    ImageEditor();
    void SetImagePath(const std::string& path);
    void SetRenderer(SDL_Renderer* r);
    void DrawImage();
};