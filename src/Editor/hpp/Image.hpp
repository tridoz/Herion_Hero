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
    void LoadImage(const std::string& path);
    void DrawImage(SDL_Renderer* r);
    void SaveImage();
};