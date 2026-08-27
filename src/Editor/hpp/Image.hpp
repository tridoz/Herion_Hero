#include "Pixel.hpp"
#include <string>
#include <vector>

#include "../../headers_only_dependencies/stb_image.h"

class Image {
  private:
    std::string filepath;
    std::vector<Pixel*> pixels;
    const int max_width = 1920, max_height = 1080;

  public:
    Image();
    auto LoadImage(const std::string&) -> void;
    auto DrawImage(SDL_Renderer*) -> void;
    auto SaveImage() -> void;
};