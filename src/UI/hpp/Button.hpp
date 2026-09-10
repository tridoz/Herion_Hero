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

  public:
    enum class State : std::uint8_t { UNACTIVE, CLICKED, FOCUSED };

  private:
    std::function<void()> OnClick;
    std::function<std::string()> OnClickReturn;

    std::unordered_map<State, std::vector<Renderable*>> renderables;
    std::vector<Renderable*> renderable;
    SDL_FRect interaction_rect;
    std::string text;

  public:
    State state;

    Button();
    auto GetInteractionRect() -> SDL_FRect*;
    auto SetInteractionRect(const SDL_FRect&) -> void;
    auto SetOnClick(std::function<void()>) -> void;
    auto SetOnClickReturn(std::function<std::string()>) -> void;
    auto Click() const -> void;
    auto ClickReturn() const -> std::string;
    auto SetRenderables(std::vector<Renderable*>) -> void;
    auto addRenderables(State, std::vector<Renderable*>) -> void;
    auto Draw(SDL_Renderer*) const -> void;
    void DrawWithOffset(SDL_Renderer*, const float, const float) const;
    std::vector<SDL_FRect> GetRects();
    void SetText(const std::string&);
    std::string GetText() const;
};

#endif // HERION_HERO_BUTTON_HPP
