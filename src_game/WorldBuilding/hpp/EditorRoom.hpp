//
// Created by tridoz on 20/05/26.
//

#ifndef HERION_HERO_EDITORROOM_HPP
#define HERION_HERO_EDITORROOM_HPP

#include "Room.hpp"
#include "../../Utils/hpp/JSONParser.hpp"


class EditorRoom : public Room {
private:
    Texture* current_editor_texture;


public:
    EditorRoom();
    void DrawAxis( SDL_Renderer* renderer ) const;

    void SetCurrentEditorTexture( Texture* texture );
    Texture* GetCurrentEditorTexture();

    void ModifyOneTile( Texture* txt, int col, int row );


    void AppendToFile( const std::string& row );
    void SaveNewEditConfiguration();

};


#endif //HERION_HERO_EDITORROOM_HPP
