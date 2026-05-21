//
// Created by tridoz on 20/05/26.
//

#ifndef HERION_HERO_EDITORROOM_HPP
#define HERION_HERO_EDITORROOM_HPP

#include "BackgroundElement.hpp"
#include "ForegroundElement.hpp"
#include "Room.hpp"
#include "../../Utils/hpp/JSONParser.hpp"

class EditorRoom : public Room {
private:
    Texture* current_editor_texture;

    float tile_width, tile_height;

    bool draw_axis;

    std::vector < std::string > base_plan_output_file;
    std::vector < std::string > foreground_output_file;
    std::vector < std::string > background_output_file;

    std::vector < ForegroundElement* > foreground_elements;
    std::vector < BackgroundElement* > background_elements;

public:
    EditorRoom();
    void DrawAxis( SDL_Renderer* renderer ) const;

    void SetCurrentEditorTexture( Texture* texture );
    Texture* GetCurrentEditorTexture();

    void ModifyOneTile( Texture* txt, int col, int row );

    void AppendToFile( const std::string& row );
    void SaveNewEditConfiguration();
    void ToggleAxis();
    bool ShouldDrawAxis() const;

};
    
#define SDL_FRECT_TOSTRING(rect) \
    ( \
    std::to_string((rect).x)  +  ";" + \
    std::to_string((rect).y)  +  ";" + \
    std::to_string((rect).w)  +  ";" + \
    std::to_string((rect).h) \
    )

#endif //HERION_HERO_EDITORROOM_HPP
