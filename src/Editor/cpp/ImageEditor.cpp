#include "../hpp/ImageEditor.hpp"

ImageEditor::ImageEditor() {
    img = new Image();
}

void ImageEditor::SetImagePath(const std::string& path) {
    img->LoadImage(path);
}

void ImageEditor::SetRenderer(SDL_Renderer* r) {
    this->renderer = r;
}

void ImageEditor::DrawImage() {
    this->img->DrawImage(renderer);
}
