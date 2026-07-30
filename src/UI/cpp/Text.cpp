//
// Created by trida on 12/10/25.
//

#include "../hpp/Text.hpp"

Text::Text() {
}

void Text::Draw(SDL_Renderer* renderer) const {

    for (int i = 0; i < this->renderable.size(); i++) {
        SDL_SetTextureBlendMode(renderable[i]->GetTexture()->GetTexture(), SDL_BLENDMODE_BLEND);
        SDL_RenderTexture(renderer, renderable[i]->GetTexture()->GetTexture(), nullptr, renderable[i]->GetRect());
    }
}

void Text::SetRenderables(std::vector<Renderable*> r) {
    this->renderable = r;
}

void Text::DrawWithOffset(SDL_Renderer* renderer, const float offset_y, const float offset_x) const {

    for (int i = 0; i < this->renderable.size(); i++) {
        Texture* texture = this->renderable[i]->GetTexture();
        SDL_FRect rect = *this->renderable[i]->GetRect();
        rect.x += offset_x;
        rect.y += offset_y;

        if (rect.y >= 0 && rect.y <= 600) {
            SDL_SetTextureBlendMode(texture->GetTexture(), SDL_BLENDMODE_BLEND);
            SDL_RenderTexture(renderer, texture->GetTexture(), nullptr, &rect);
        }
    }
}
