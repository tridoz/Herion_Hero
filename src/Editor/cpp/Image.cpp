#include "../hpp/Image.hpp"

#include <iostream>

Image::Image() {
}

void Image::LoadImage(const std::string& path) {

    int width, height, channels;

    unsigned char* pixels = stbi_load(path.c_str(), &width, &height, &channels, 0);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * 4;
            this->pixels.emplace_back(
                new Pixel(pixels[index], pixels[index + 1], pixels[index + 2], pixels[index + 3])
            );

            constexpr float scale = 16.0f;

            this->pixels.back()->SetRect(new SDL_FRect{
                .x = static_cast<float>(x) * scale, .y = static_cast<float>(y) * scale, .w = scale, .h = scale
            });
        }
    }
}

void Image::DrawImage(SDL_Renderer* r) {
    for (Pixel* p : pixels) {
        p->Draw(r);
    }
}