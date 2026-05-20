//
// Created by tridoz on 20/05/26.
//

#include "../hpp/EditorRoom.hpp"

EditorRoom::EditorRoom() {}

void EditorRoom::DrawAxis(SDL_Renderer* renderer) const {

    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );

    const int width = JSONParser::graphics::GetWidth();
    const int height = JSONParser::graphics::GetHeight();

    const float tile_width = width / horizontal_tiles;
    const float tile_height = height / vertical_tiles;

    for ( int i = 0 ; i <= horizontal_tiles ; ++i ) {
        SDL_RenderLine( renderer, i*tile_width, 0, i*tile_width, height );
    }

    for ( int i = 0 ; i <= vertical_tiles ; ++i ) {
        SDL_RenderLine( renderer, 0, i*tile_height, width, i*tile_height );
    }

}

void EditorRoom::SetCurrentEditorTexture(Texture *texture) {
    this->current_editor_texture = texture;
}

Texture *EditorRoom::GetCurrentEditorTexture() {
    return current_editor_texture;
}

void EditorRoom::AppendToFile(const std::string &row) {
    base_plan_output_file.push_back( row );
}

void EditorRoom::SaveNewEditConfiguration() {
    for ( const auto& row : tiles ) {
        std::string str_row;
        for ( const auto& tile : row ) {
            str_row += tile->GetCode() + " ";
        }
        AppendToFile( str_row );
    }

    std::ofstream output_file_stream;

    try {
        FileOpener::OpenFileOutput( output_file_stream, filepath );
    } catch ( HerionException::File::FileException& ex ) {
        ex.UpdateStackTrace( GET_CONTEXT() );
        throw;
    }

    for ( const auto& line : base_plan_output_file ) {
        output_file_stream << line << std::endl;
    }

}

void EditorRoom::ToggleAxis() {
    draw_axis = !draw_axis;
}

bool EditorRoom::ShouldDrawAxis() const {
    return draw_axis;
}
