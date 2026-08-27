//
// Created by david on 21/11/2025.
//

#include <utility>

#include "../hpp/Button.hpp"

Button::Button() = default;

auto Button::SetOnClick(std::function<void()> action) -> void {
    this->OnClick = std::move(action);
}

auto Button::SetOnClickReturn(std::function<std::string()> action) -> void {
    this->OnClickReturn = std::move(action);
}

auto Button::Click() const -> void {

    if (OnClick) {
        OnClick();
    }
}

auto Button::ClickReturn() const -> std::string {
    if (OnClickReturn) {
        return OnClickReturn();
    }
    return {};
}

auto Button::SetRenderables(std::vector<Renderable*> r) -> void {
    this->renderable = std::move(r);
}

auto Button::Draw(SDL_Renderer* renderer) const -> void {

    for (int i = 0; i < this->renderable.size(); i++) {
        SDL_SetTextureBlendMode(renderable[i]->GetTexture()->GetTexture(), SDL_BLENDMODE_BLEND);
        SDL_RenderTexture(renderer, renderable[i]->GetTexture()->GetTexture(), nullptr, renderable[i]->GetRect());
    }
}

auto Button::DrawWithOffset(SDL_Renderer* renderer, const float offset_y, const float offset_x) const -> void {

    for (int i = 0; i < this->renderable.size(); i++) {
        Texture* texture = this->renderable[i]->GetTexture();
        SDL_FRect rect = *this->renderable[i]->GetRect();
        rect.x += offset_x;
        rect.y += offset_y;

        if (rect.y >= 0 && rect.y <= 300) {
            SDL_SetTextureBlendMode(texture->GetTexture(), SDL_BLENDMODE_BLEND);
            SDL_RenderTexture(renderer, texture->GetTexture(), nullptr, &rect);
        }
    }
}

auto Button::SetText(const std::string& text_to_set) -> void {
    this->text = text_to_set;
}

auto Button::GetText() const -> std::string {
    return text;
}

auto Button::GetRects() -> std::vector<SDL_FRect> {
    std::vector<SDL_FRect> rects;
    rects.reserve(renderable.size());

    for (auto ren : renderable) {
        rects.emplace_back(*ren->GetRect());
    }

    return rects;
}
