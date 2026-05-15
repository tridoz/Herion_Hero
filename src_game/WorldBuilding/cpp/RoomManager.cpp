//
// Created by david on 18/11/2025.
//

#include "../hpp/RoomManager.hpp"

#include <set>

#include "../../Utils/hpp/JSONParser.hpp"

RoomManager::RoomManager() {
    spawn_room = nullptr;
    current_room = nullptr;
}

RoomManager::~RoomManager() {
    if (!spawn_room) return;

    std::set<Node*> visited;

    std::function<void(Node*)> FreeNode = [&](Node* node) {
        if (!node || visited.count(node)) return;
        visited.insert(node);

        FreeNode(node->left);
        FreeNode(node->right);
        FreeNode(node->up);
        FreeNode(node->down);

        delete node->room;
        delete node;
    };

    FreeNode(spawn_room);

    spawn_room = nullptr;
    current_room = nullptr;
}

void RoomManager::GenerateEditorRoom( Room* room, const std::string& map_path ) {

    std::vector< std::vector <Tile* > > tiles;
    const float w = JSONParser::graphics::GetWidth() / horizontal_tiles;
    const float h = JSONParser::graphics::GetHeight() / vertical_tiles;

    std::ifstream map_file;

    try {
        FileOpener::OpenFileInput( map_file, map_path );
    } catch ( HerionException::File::FileException& ex ) {
        ex.UpdateStackTrace( GET_CONTEXT() );
        throw;
    }

    std::string line;
    int y = 0;

    while (std::getline(map_file, line)) {
        std::stringstream ss(line);
        std::string cell;

        std::vector<Tile*> row;
        int x = 0;

        if (line.starts_with("#") || line.empty() ) {
            continue;
        }

        if ( line.starts_with('?') ) {
            char a;
            int x, y;
            ss >> a;
            ss >> y;
            ss >> x;
            room->SetSpawnCoord( x, y );
            continue;
        }

        while (ss >> cell) {

            Tile* tile = new Tile();
            std::string texture_path;

            if (cell == "FB") {
                texture_path = "Assets/WorldBuilding/Floor/BaseFloor.png";
            } else if (cell == "CB") {
                texture_path = "Assets/WorldBuilding/Ceiling/BaseCeiling.png";
            } else if (cell == ".") {
                texture_path = "Assets/WorldBuilding/Background/Nothing.png";
            }

            tile->SetTexture(textureManager->GetTexture(texture_path));
            tile->SetRect(x * w, y * h, w, h);
            row.push_back(tile);

            x++;
        }
        tiles.push_back(row);
        y++;

    }

    room->SetTiles( tiles );

}

void RoomManager::GenerateRoom(  Direction dir ) {


    std::vector<std::vector<Tile*> > tiles;


    const float w = JSONParser::graphics::GetWidth() / horizontal_tiles;
    const float h = JSONParser::graphics::GetHeight() / vertical_tiles;


    std::ifstream map_file;

    Node* newRoom = new Node();
    newRoom->room = new Room();

    try {
        FileOpener::OpenFileInput( map_file, "../maps/room1/map.hhmap" );
    } catch (HerionException::File::FileException& ex ) {
        ex.UpdateStackTrace( GET_CONTEXT()   );
        throw;
    }

    std::string line;
    int y = 0;

    while (std::getline(map_file, line)) {
        std::stringstream ss(line);
        std::string cell;

        std::vector<Tile*> row;
        int x = 0;

        if (line.starts_with("#") || line.empty() ) {
            continue;
        }

        if ( line.starts_with('?') ) {
            char a;
            int x, y;
            ss >> a;
            ss >> y;
            ss >> x;
            newRoom->room->SetSpawnCoord( x, y );
            continue;
        }

        while (ss >> cell) {

            Tile* tile = new Tile();
            std::string texture_path;

            if (cell == "FB") {
                texture_path = "Assets/WorldBuilding/Floor/BaseFloor.png";
            } else if (cell == "CB") {
                texture_path = "Assets/WorldBuilding/Ceiling/BaseCeiling.png";
            } else if (cell == ".") {
                texture_path = "Assets/WorldBuilding/Background/Nothing.png";
            }

            tile->SetTexture(textureManager->GetTexture(texture_path));
            tile->SetRect(x * w, y * h, w, h);
            row.push_back(tile);

            x++;
        }
        tiles.push_back(row);
        y++;

    }


    newRoom->room->SetTiles( tiles );


    if ( spawn_room == nullptr ) {
        spawn_room = newRoom;
        current_room = spawn_room;
    }else {
        switch ( dir ) {
            case DIR_UP:
                current_room -> up = newRoom;
                current_room -> up -> down = current_room;
                break;

            case DIR_LEFT:
                current_room -> left = newRoom;
                current_room -> left -> right = current_room;
                break;

            case DIR_DOWN:
                current_room -> down = newRoom;
                current_room -> down -> up = current_room;
                break;

            case DIR_RIGHT:
                current_room -> right = newRoom;
                current_room -> right -> left = current_room;
                break;

        }

    }

}

Room* RoomManager::GetCurrentRoom() const {
    return this->current_room->room;
}

void RoomManager::GoLeft() {

    if ( current_room->left == nullptr ) {
        GenerateRoom( DIR_LEFT);
    }

    current_room = current_room->left;
}

void RoomManager::GoRight() {
    if ( current_room->right == nullptr ) {
        GenerateRoom( DIR_RIGHT);
    }

    current_room = current_room->right;
}

void RoomManager::GoUp() {

    if ( current_room->up == nullptr ) {
        GenerateRoom( DIR_UP);
    }

    current_room = current_room->up;
}

void RoomManager::GoDown() {
    if ( current_room->down == nullptr ) {
        GenerateRoom( DIR_DOWN);
    }

    current_room = current_room->down;
}

void RoomManager::ResizeRoom() {
    std::vector < std::vector< Tile* > > tiles = this->current_room->room->GetTiles();
    int w, h;
    try {
        w = JSONParser::graphics::GetWidth();
        h = JSONParser::graphics::GetHeight();
    } catch ( HerionException::File::FileMalformedException& ex ) {
        ex.UpdateStackTrace( GET_CONTEXT() );
        throw;
    }

    for ( int x = 0 ; x < tiles.size() ; x++ ) {
        for ( int y = 0 ; y < tiles[x].size() ; y++ ) {
            float newW, newH;

            newW = w / horizontal_tiles;
            newH = h / vertical_tiles;

            tiles[x][y] -> SetRect( y*newW, x*newH, newW, newH  );

        }
    }
}

void RoomManager::ResizeEditorRoom( Room* room ) {
    std::vector < std::vector < Tile* > > tiles = room->GetTiles();

    int w, h;

    try {
        w = JSONParser::graphics::GetWidth();
        h = JSONParser::graphics::GetHeight();
    } catch ( HerionException::File::FileMalformedException& ex ) {
        ex.UpdateStackTrace( GET_CONTEXT() );
        throw;
    }

    for ( int x = 0 ; x < tiles.size() ; x++ ) {
        for ( int y = 0 ; y < tiles[x].size() ; y++ ) {
            float newW, newH;

            newW = w / horizontal_tiles;
            newH = h / vertical_tiles;

            tiles[x][y] -> SetRect( y*newW, x*newH, newW, newH  );

        }
    }
}

void RoomManager::DrawCurrentRoom( SDL_Renderer* renderer) const {
    current_room->room->Draw( renderer );
}

void RoomManager::SetDimensions(int screen_width, int screen_height, int horizontal_tiles, int vertical_tiles) {
    this->screen_width = screen_width;
    this->screen_height = screen_height;
    this->horizontal_tiles = horizontal_tiles;
    this->vertical_tiles = vertical_tiles;
}

void RoomManager::SetTextureManager(TextureManager* texture_manager) {
    this->textureManager = texture_manager;
}

int RoomManager::GetPlayerSpawnCellX() const {
    return this->current_room->room->GetSpawnX() * (  JSONParser::graphics::GetWidth() / this->horizontal_tiles );
}

int RoomManager::GetPlayerSpawnCellY() const {
    return  this->current_room->room->GetSpawnY()  * ( JSONParser::graphics::GetHeight() / this->vertical_tiles  );
}
