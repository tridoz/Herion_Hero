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

void RoomManager::GenerateRoom( ROOM_TYPE room_type, Direction dir ) {

    std::string room_type_path;

    switch ( room_type ) {
        default:
            room_type_path = "no_texture";
            break;

        case ANCIENT_RUINS:
            room_type_path = "ancient_ruins";
            break;

        case LAVA:
            room_type_path = "lava";
            break;

        case ICE:
            room_type_path = "ice";
            break;

        case DARK:
            room_type_path = "dark";
            break;

        case HOLY:
            room_type_path = "holy";
            break;

        case POISON:
            room_type_path = "poison";
            break;
    }

    std::vector<std::vector<Tile*> > tiles;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 8);

    const float w = JSONParser::graphics::GetWidth() / horizontal_tiles;
    const float h = JSONParser::graphics::GetHeight() / vertical_tiles;

    for ( int i = 0 ; i < horizontal_tiles ; i++ ) {

        std::vector<Tile*> row;

        for ( int j = 0 ; j < vertical_tiles ; j++ ) {

            Tile* tile = new Tile();

            int texture_type = dis(gen);
            std::string texture_path;

            switch ( texture_type ) {
                default:
                    texture_path = "assets/floors/" + room_type_path + "/" + room_type_path + "_base_floor.png";
                    break;
                case 0:
                    texture_path = "assets/floors/" + room_type_path + "/" + room_type_path + "_base_floor.png";
                    break;
                case 1:
                    texture_path = "assets/floors/" + room_type_path + "/" + room_type_path + "_cracked_floor_1.png";
                    break;
                case 2:
                    texture_path = "assets/floors/" + room_type_path + "/" + room_type_path + "_cracked_floor_2.png";
                    break;
                case 3:
                    texture_path = "assets/floors/" + room_type_path + "/" + room_type_path + "_cracked_floor_3.png";
                    break;
                case 4:
                    texture_path = "assets/floors/" + room_type_path + "/" + room_type_path + "_cracked_floor_4.png";
                    break;
                case 5:
                    texture_path = "assets/floors/" + room_type_path + "/" + room_type_path + "_cracked_floor_5.png";
                    break;
                case 6:
                    texture_path = "assets/floors/" + room_type_path + "/" + room_type_path + "_cracked_floor_6.png";
                    break;
                case 7:
                    texture_path = "assets/floors/" + room_type_path + "/" + room_type_path + "_cracked_floor_7.png";
                    break;
                case 8:
                    texture_path = "assets/floors/" + room_type_path + "/" + room_type_path + "_cracked_floor_8.png";
                    break;
            }

            tile->SetTexture( textureManager->GetTexture(texture_path) );
            tile->SetRect( i*w , j*h , w, h );

            row.push_back( tile );

        }

        tiles.push_back( row );

    }

    // Logger::LogOk(
    //     std::time(nullptr),
    //     "TILES",
    //     "RoomManager",
    //     "GenerateSpawnRoom",
    //     "All tiles created successfully"
    //     );

    Node* newRoom = new Node();
    newRoom->room = new Room();
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

    // Logger::LogOk(
    //     std::time(nullptr),
    //     "SETTING",
    //     "RoomManager",
    //     "GenerateSpawnRoom",
    //     "Spawn room generated correctly"
    //     );
}

void RoomManager::GoLeft() {

    if ( current_room->left == nullptr ) {
        GenerateRoom( ICE, DIR_LEFT );
    }

    current_room = current_room->left;
}

void RoomManager::GoRight() {
    if ( current_room->right == nullptr ) {
        GenerateRoom( ICE, DIR_RIGHT );
    }

    current_room = current_room->right;
}

void RoomManager::GoUp() {

    if ( current_room->up == nullptr ) {
        GenerateRoom( ICE, DIR_UP );
    }

    current_room = current_room->up;
}

void RoomManager::GoDown() {
    if ( current_room->down == nullptr ) {
        GenerateRoom( ICE, DIR_DOWN );
    }

    current_room = current_room->down;
}

void RoomManager::ResizeRoom() {
    std::vector < std::vector< Tile* > > tiles = this->current_room->room->GetTiles();
    for ( int i = 0 ; i < tiles.size() ; i++ ) {
        for ( int j = 0 ; j < tiles[i].size() ; j++ ) {
            float newX, newY, newW, newH;

            newW = JSONParser::graphics::GetWidth() / horizontal_tiles;
            newH = JSONParser::graphics::GetHeight() / vertical_tiles;


            tiles[i][j] -> SetRect( i*newW, j*newH, newW, newH  );

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
