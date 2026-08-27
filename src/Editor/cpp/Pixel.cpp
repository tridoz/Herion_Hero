#include "../hpp/Pixel.hpp"

Pixel::Pixel(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

auto Pixel::SetRect(SDL_FRect* rect) -> void {
    this->rect = rect;
}

auto Pixel::Draw(SDL_Renderer* ren) -> void {
    SDL_SetRenderDrawColor(ren, r, g, b, a);
    SDL_RenderFillRect(ren, rect);
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
}