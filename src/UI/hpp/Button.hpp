//
// Created by david on 21/11/2025.
//

#ifndef HERION_HERO_BUTTON_HPP
#define HERION_HERO_BUTTON_HPP

#include <SDL3/SDL.h>
#include <functional>

#include "../../Textures/hpp/Renderable.hpp"
#include "../../Utils/hpp/Logger.hpp"

class Button {
  private:
    std::function<void()> OnClick;
    std::function<std::string()> OnClickReturn;

    std::vector<Renderable*> renderable;
    std::string text;

  public:
    Button();
    void SetOnClick(std::function<void()> action);
    void SetOnClickReturn(std::function<std::string()> action);
    void Click() const;
    std::string ClickReturn() const;
    void SetRenderables(std::vector<Renderable*> renderables);
    void Draw(SDL_Renderer* renderer) const;
    void DrawWithOffset(SDL_Renderer* renderer, const float offset_y, const float offset_x) const;
    std::vector<SDL_FRect> GetRects();
    void SetText(const std::string& text_to_set);
    std::string GetText() const;

    static constexpr auto reflect_members() {
        return std::make_tuple(
            Field<Button, std::function<void()>>{"OnClick", &Button::OnClick},
            Field<Button, std::function<std::string()>>{"OnClickReturn", &Button::OnClickReturn},
            Field<Button, std::string>{"text", &Button::text}
        );
    }
};

#endif // HERION_HERO_BUTTON_HPP
