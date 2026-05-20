//
// Created by david on 17/11/2025.
//

#include "../hpp/Room.hpp"

#include "../../Utils/hpp/JSONParser.hpp"

Room::Room() {}

Room::~Room() {

    for ( std::vector<Tile*> & tile_row : tiles) {
        for (const Tile* tile : tile_row) {
            delete tile;
        }
    }

    tiles.clear();

}

std::vector< std::vector<Tile* > > Room::GetTiles() {
    return this->tiles;
}

void Room::Draw(SDL_Renderer* renderer) {

    for ( std::vector<Tile*> & tiles_row : tiles) {
        for ( Tile* & tile : tiles_row) {
            tile->Draw(renderer);
        }
    }

}

void Room::DrawAxis(SDL_Renderer* renderer) const {

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

void Room::SetTiles(const std::vector<std::vector<Tile*>> &new_tiles) {
    this->tiles = new_tiles;
    this->horizontal_tiles = this->tiles[0].size();
    this->vertical_tiles =  this->tiles.size();
}

void Room::SetSpawnCoord(int x, int y) {
    this -> spawn_x = x;
    this -> spawn_y = y;
}

int Room::GetSpawnX() const {
    return spawn_x;
}

int Room::GetSpawnY() const {
    return spawn_y;
}

Texture *Room::GetCurrentEditorTexture() {
    return current_editor_texture;
}

void Room::SetCurrentEditorTexture(Texture *texture) {
    this->current_editor_texture = texture;
}

int Room::GetHorizontalTiles() {
    return horizontal_tiles;
}

int Room::GetVerticalTiles() {
    return vertical_tiles;
}

void Room::AppendToFile(const std::string &row) {
    output_file.push_back( row );
}

void Room::SetFilepath(const std::string &filepath) {
    this->filepath = filepath;
}

void Room::SaveNewEditConfiguration() {
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

    for ( const auto& line : output_file ) {
        output_file_stream << line << std::endl;
    }

}

