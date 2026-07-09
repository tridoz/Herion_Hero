//
// Created by tridoz on 20/05/26.
//

#ifndef HERION_HERO_EDITORROOM_HPP
#define HERION_HERO_EDITORROOM_HPP

#include "BackgroundElement.hpp"
#include "ForegroundElement.hpp"
#include "../../Utils/hpp/Reflector.hpp"
#include "Room.hpp"
#include "../../Utils/hpp/JSONParser.hpp"
#include "../../UI/hpp/Button.hpp"
#include <unordered_map>

class EditorRoom : public Room {
private:
    Texture* current_editor_texture;

    bool draw_axis;
    bool draw_hitboxes;

    std::vector < std::vector < bool > > hitboxes;
    std::unordered_map<std::string, std::vector<Button*>> buttons;

    std::string action;
    std::string current_entity_to_set;

    std::vector < std::string > base_plan_output_file;
    std::vector < std::string > foreground_output_file;
    std::vector < std::string > background_output_file;
    std::vector < std::string > hitboxes_output_file;

    std::vector < ForegroundElement* > foreground_elements;
    std::vector < BackgroundElement* > background_elements;

public:
    EditorRoom();

    void DrawAxis( SDL_Renderer* renderer ) const;
    void DrawHitboxes( SDL_Renderer* renderer ) const;

    void SetCurrentEditorTexture( Texture* texture );
    Texture* GetCurrentEditorTexture();

    void AppendToFile(const std::string &row, std::vector<std::string> &vect);
    void SaveNewEditConfiguration();

    void ToggleAxis();
    bool ShouldDrawAxis() const;

    void ToggleHitboxes();
    bool ShouldDrawHitboxes() const;

    void SetAction( const std::string& action );
    std::string GetAction() const;

    void SetCurrentEntityToSet( const std::string& action );
    std::string GetCurrentEntity() const;

    void AddButton(Button* btn, std::string name);
    int GetEntitiCount(std::string name);

    void SetHitboxes();
    void UpdateHitbox( int cell_x, int cell_y );

    void Draw( SDL_Renderer* renderer );

    std::vector < std::string >& GetBasePlaneVector();
    std::vector < std::string >& GetForegroundVector();
    std::vector < std::string >& GetBackgroundVector();

    static constexpr auto reflect_members() {

        return concat_tuple(
            Room::reflect_members(),
            std::make_tuple(
                Field<EditorRoom, Texture*>{"current_editor_texture", &EditorRoom::current_editor_texture},
                Field<EditorRoom, bool>{"draw_axis", &EditorRoom::draw_axis},
                Field<EditorRoom, bool>{"draw_hitboxes", &EditorRoom::draw_hitboxes},
                Field<EditorRoom, std::vector<std::vector<bool>>>{"hitboxes", &EditorRoom::hitboxes},
                Field<EditorRoom, std::string>{"action", &EditorRoom::action},
                Field<EditorRoom, std::vector<std::string>>{"base_plan_output_file", &EditorRoom::base_plan_output_file},
                Field<EditorRoom, std::vector<std::string>>{"foreground_output_file", &EditorRoom::foreground_output_file},
                Field<EditorRoom, std::vector<std::string>>{"background_output_file", &EditorRoom::background_output_file},
                Field<EditorRoom, std::vector<std::string>>{"hitboxes_output_file", &EditorRoom::hitboxes_output_file},
                Field<EditorRoom, std::vector<ForegroundElement*>>{"foreground_elements", &EditorRoom::foreground_elements},
                Field<EditorRoom, std::vector<BackgroundElement*>>{"background_elements", &EditorRoom::background_elements}
            )
        );
    }

};

#define SDL_FRECT_TOSTRING(rect) \
    ( \
    std::to_string((rect).x)  +  ";" + \
    std::to_string((rect).y)  +  ";" + \
    std::to_string((rect).w)  +  ";" + \
    std::to_string((rect).h) \
    )

#endif //HERION_HERO_EDITORROOM_HPP
