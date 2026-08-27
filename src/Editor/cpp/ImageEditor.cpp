#include "../hpp/ImageEditor.hpp"

ImageEditor::ImageEditor() {
    img = new Image();
}

auto ImageEditor::SetImagePath(const std::string& path) -> void {
    img->LoadImage(path);
}

auto ImageEditor::SetRenderer(SDL_Renderer* r) -> void {
    this->renderer = r;
}

auto ImageEditor::DrawImage() -> void {
    this->img->DrawImage(renderer);
}
