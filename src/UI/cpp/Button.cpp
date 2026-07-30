//
// Created by david on 21/11/2025.
//

#include "../hpp/Button.hpp"

Button::Button() = default;

void Button::SetOnClick(std::function<void()> action) {
    this->OnClick = action;
}

void Button::SetOnClickReturn(std::function<std::string()> action) {
    this->OnClickReturn = action;
}

void Button::Click() const {

    if (OnClick) {
        OnClick();
    }
}

std::string Button::ClickReturn() const {
    if (OnClickReturn) {
        return OnClickReturn();
    }
    return {};
}

void Button::SetRenderables(std::vector<Renderable*> r) {
    this->renderable = r;
}

void Button::Draw(SDL_Renderer* renderer) const {

    for (int i = 0; i < this->renderable.size(); i++) {
        SDL_SetTextureBlendMode(renderable[i]->GetTexture()->GetTexture(), SDL_BLENDMODE_BLEND);
        SDL_RenderTexture(renderer, renderable[i]->GetTexture()->GetTexture(), nullptr, renderable[i]->GetRect());
    }
}

void Button::DrawWithOffset(SDL_Renderer* renderer, const float offset_y, const float offset_x) const {

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

void Button::SetText(const std::string& text_to_set) {
    this->text = text_to_set;
}

std::string Button::GetText() const {
    return text;
}

std::vector<SDL_FRect> Button::GetRects() {
    std::vector<SDL_FRect> rects;

    for (auto ren : renderable) {
        rects.emplace_back(*ren->GetRect());
    }

    return rects;
}
