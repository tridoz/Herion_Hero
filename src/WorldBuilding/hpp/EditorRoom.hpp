//
// Created by tridoz on 20/05/26.
//

#ifndef HERION_HERO_EDITORROOM_HPP
#define HERION_HERO_EDITORROOM_HPP

#include "../../UI/hpp/Button.hpp"
#include "../../Utils/hpp/JSONParser.hpp"
#include "BackgroundElement.hpp"
#include "ForegroundElement.hpp"
#include "Room.hpp"
#include <unordered_map>

class EditorRoom : public Room {
  private:
    Texture* current_editor_texture;

    bool draw_axis;
    bool draw_hitboxes;

    std::vector<std::vector<bool>> hitboxes;
    std::unordered_map<std::string, std::vector<Button*>> buttons;

    std::string action;
    std::string current_entity_to_set;

    std::vector<std::string> base_plan_output_file;
    std::vector<std::string> foreground_output_file;
    std::vector<std::string> background_output_file;
    std::vector<std::string> hitboxes_output_file;

    std::vector<ForegroundElement*> foreground_elements;
    std::vector<BackgroundElement*> background_elements;

  public:
    EditorRoom();
    ~EditorRoom();

    auto DrawAxis(SDL_Renderer*) const -> void;
    auto DrawHitboxes(SDL_Renderer*) const -> void;

    auto SetCurrentEditorTexture(Texture*) -> void;
    auto GetCurrentEditorTexture() -> Texture*;

    auto AppendToFile(const std::string&, std::vector<std::string>&) -> void;
    auto SaveNewEditConfiguration() -> void;

    auto ToggleAxis() -> void;
    auto ShouldDrawAxis() const -> bool;

    auto ToggleHitboxes() -> void;
    auto ShouldDrawHitboxes() const -> bool;

    auto SetAction(const std::string&) -> void;
    auto GetAction() const -> std::string;

    auto SetCurrentEntityToSet(const std::string&) -> void;
    auto GetCurrentEntity() const -> std::string;

    auto AddButton(Button*, std::string) -> void;
    auto GetEntitiCount(const std::string&) const -> int;

    auto SetHitboxes() -> void;
    auto UpdateHitbox(int, int) -> void;

    auto Draw(SDL_Renderer*) -> void;

    auto GetBasePlaneVector() -> std::vector<std::string>&;
    auto GetForegroundVector() -> std::vector<std::string>&;
    auto GetBackgroundVector() -> std::vector<std::string>&;
};

#define SDL_FRECT_TOSTRING(rect)                                                                                       \
    (std::to_string((rect).x) + ";" + std::to_string((rect).y) + ";" + std::to_string((rect).w) + ";" +                \
     std::to_string((rect).h))

#endif // HERION_HERO_EDITORROOM_HPP
