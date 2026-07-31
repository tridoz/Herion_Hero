#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <SDL3/SDL_iostream.h>

#include <cstdint>

class Pixel {
  private:
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;
    std::uint8_t a;
    SDL_FRect* rect;

  public:
    Pixel(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a);
    void SetRect(SDL_FRect* rect);
    void Draw(SDL_Renderer* r);
};