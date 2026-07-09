//
// Created by tridoz on 20/05/26.
//

#include "../hpp/EditorRoom.hpp"

EditorRoom::EditorRoom() {
    this->draw_axis = true;
    this->draw_hitboxes = false;
    this->width = JSONParser::graphics::GetWidth();
    this->height = JSONParser::graphics::GetHeight();
    this->current_editor_texture = nullptr;
}

void EditorRoom::DrawAxis(SDL_Renderer* renderer) const {

    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );

    for ( int i = 0 ; i <= horizontal_tiles ; ++i ) {
        SDL_RenderLine( renderer, i*tile_width, 0, i*tile_width, height );
    }

    for ( int i = 0 ; i <= vertical_tiles ; ++i ) {
        SDL_RenderLine( renderer, 0, i*tile_height, width, i*tile_height );
    }

}

void EditorRoom::SetHitboxes() {

    for (size_t j = 0; j < tiles.size(); ++j) {
        std::vector < bool > row;
        for (size_t i = 0; i < tiles[j].size(); ++i) {
            bool hitbox = tiles[j][i]->HasHitbox();
            row.push_back(hitbox);
        }
        hitboxes.push_back(row);
    }

}

void EditorRoom::UpdateHitbox(int cell_x, int cell_y) {
    this->hitboxes[cell_y][cell_x] = !this->hitboxes[cell_y][cell_x];
}

void EditorRoom::DrawHitboxes(SDL_Renderer* renderer) const {
    for (size_t j = 0; j < hitboxes.size(); ++j) {
        for (size_t i = 0; i < hitboxes[j].size(); ++i) {
            bool hitbox = hitboxes[j][i];

            if (hitbox) {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

                SDL_FRect rect;
                rect.x = i * tile_width;
                rect.y = j * tile_height;
                rect.w = tile_width;
                rect.h = tile_height;

                SDL_RenderRect(renderer, &rect);
            }
        }
    }
}

void EditorRoom::Draw(SDL_Renderer* r) {
    for ( std::vector<Tile*> & tiles_row : tiles) {
        for ( Tile* & tile : tiles_row) {
            tile->Draw(r);
        }
    }

    for( const auto [name, btns] : buttons ) {
        for( Button* b : btns ) {
            b->Draw(r);
        }
    }
}

void EditorRoom::SetCurrentEditorTexture(Texture *texture) {
    this->current_editor_texture = texture;
}

Texture *EditorRoom::GetCurrentEditorTexture() {
    return current_editor_texture;
}

void EditorRoom::AppendToFile(const std::string &row, std::vector<std::string>& vect ) {
    vect.push_back( row );
}

void EditorRoom::SaveNewEditConfiguration() {


    for ( const auto& row : tiles ) {
        std::string str_row;
        for ( const auto& tile : row ) {
            str_row += tile->GetCode() + " ";
        }
        AppendToFile( str_row, this->base_plan_output_file );
    }

    for ( const auto& row : hitboxes ) {
        std::string str_row;
        for ( bool hitbox : row ) {
            str_row += std::to_string( hitbox ) + " ";
        }
        AppendToFile( str_row, this->hitboxes_output_file );
    }

    std::ofstream base_place_output_file_stream;
    std::ofstream hitbox_output_file_stream;

    try {
        FileOpener::OpenFileOutput( base_place_output_file_stream, filepath + "base_plane_textures.hhmap" );
        FileOpener::OpenFileOutput( hitbox_output_file_stream, filepath + "hitboxes.hhmap" );
    } catch ( HerionException::File::FileException& ex ) {
        ex.UpdateStackTrace( GET_CONTEXT() );
        throw;
    }

    for ( const auto& line : base_plan_output_file ) {
        base_place_output_file_stream << line << std::endl;
    }

    for ( const auto& line : hitboxes_output_file ) {
        hitbox_output_file_stream << line << std::endl;
    }

    this->base_plan_output_file.erase( base_plan_output_file.begin() + 2 , base_plan_output_file.end()  );
    this->hitboxes_output_file.clear();

}

void EditorRoom::ToggleAxis() {
    draw_axis = !draw_axis;
}

bool EditorRoom::ShouldDrawAxis() const {
    return draw_axis;
}

void EditorRoom::ToggleHitboxes() {
    draw_hitboxes = !draw_hitboxes;
}

bool EditorRoom::ShouldDrawHitboxes() const {
    return draw_hitboxes;
}

void EditorRoom::SetAction(const std::string &action) {
    this->action = action;
}

std::string EditorRoom::GetAction() const {
    return this->action;
}

void EditorRoom::SetCurrentEntityToSet( const std::string& entity ) {
    this->current_entity_to_set = entity;
}

std::string EditorRoom::GetCurrentEntity() const {
    return this->current_entity_to_set;
}

std::vector<std::string> &EditorRoom::GetBackgroundVector() {
    return this->background_output_file;
}

std::vector<std::string> &EditorRoom::GetForegroundVector() {
    return this->foreground_output_file;
}

std::vector<std::string> &EditorRoom::GetBasePlaneVector() {
    return this->base_plan_output_file;
}

void EditorRoom::AddButton(Button* btn, std::string name) {
    if( this->buttons.contains(name) ) {
        this->buttons.at(name).emplace_back(btn);
    } else {
        std::vector<Button*> b{btn};
        this->buttons.emplace(name, b);
    }
}

int EditorRoom::GetEntitiCount(std::string name ) {
    return this->buttons.contains(name)? buttons.at(name).size(): 0;
}
