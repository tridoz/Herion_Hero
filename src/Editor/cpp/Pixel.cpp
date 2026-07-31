#include "../hpp/Pixel.hpp"

Pixel::Pixel(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void Pixel::SetRect(SDL_FRect* rect) {
    this->rect = rect;
}

void Pixel::Draw(SDL_Renderer* ren) {
    SDL_SetRenderDrawColor(ren, r, g, b, a);
    SDL_RenderFillRect(ren, rect);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
}