//
// Created by david on 18/11/2025.
//

#include "../hpp/RoomManager.hpp"

#include <set>

#include "../../Utils/hpp/JSONParser.hpp"

class EditorRoom;

RoomManager::RoomManager() {
    spawn_room = nullptr;
    current_room = nullptr;
}

RoomManager::~RoomManager() {
    if (!spawn_room)
        return;

    std::set<Node*> visited;

    std::function<void(Node*)> FreeNode = [&](Node* node) {
        if (!node || visited.count(node))
            return;
        visited.insert(node);

        FreeNode(node->left);
        FreeNode(node->right);
        FreeNode(node->up);
        FreeNode(node->down);

        delete node->room;
        delete node;
    };

    FreeNode(spawn_room);

    delete textureManager;
    textureManager = nullptr;

    spawn_room = nullptr;
    current_room = nullptr;
}

auto RoomManager::GenerateEditorRoom(EditorRoom* room, const std::string& map_path) -> void {

    std::vector<std::vector<Tile*>> tiles;
    const float w = static_cast<float>(JSONParser::graphics::GetWidth()) / static_cast<float>(horizontal_tiles);
    const float h = static_cast<float>(JSONParser::graphics::GetHeight()) / static_cast<float>(vertical_tiles);

    std::string map_filepath = map_path + "base_plane_textures.hhmap";
    std::string hitboxes_filepath = map_path + "hitboxes.hhmap";

    std::ifstream map_file;
    std::ifstream hitbox_file;

    try {
        FileOpener::OpenFileInput(map_file, map_filepath);
        FileOpener::OpenFileInput(hitbox_file, hitboxes_filepath);
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    room->SetFilepath(map_path);

    std::string base_plane_line;
    std::string hitbox_line;
    int y = 0;

    while (std::getline(map_file, base_plane_line)) {

        std::stringstream base_plan_ss(base_plane_line);

        std::string base_plane_cell;
        std::string hitbox_cell;

        std::vector<Tile*> row;
        int x = 0;

        if (base_plane_line.starts_with("#") || base_plane_line.empty()) {
            room->AppendToFile(base_plane_line, room->GetBasePlaneVector());
            continue;
        }

        if (base_plane_line.starts_with('?')) {
            char a;
            int x, y;
            base_plan_ss >> a;
            base_plan_ss >> y;
            base_plan_ss >> x;
            room->SetSpawnCoord(x, y);
            room->AppendToFile(base_plane_line, room->GetBasePlaneVector());
            continue;
        }

        std::getline(hitbox_file, hitbox_line);
        std::stringstream hitbox_ss(hitbox_line);

        while (base_plan_ss >> base_plane_cell) {
            hitbox_ss >> hitbox_cell;

            Tile* tile = new Tile();

            tile->SetTexture(textureManager->GetTextureByCode(base_plane_cell));
            tile->SetRect(static_cast<float>(x) * w, static_cast<float>(y) * h, w, h);
            bool hitbox = std::atoi(hitbox_cell.c_str());
            tile->SetHitbox(hitbox);
            row.push_back(tile);

            x++;
        }
        tiles.push_back(row);
        y++;
    }

    room->SetTiles(tiles);
    room->SetHitboxes();
}

auto RoomManager::GenerateRoom(DIRECTION dir, const std::string& map_path) -> void {

    std::vector<std::vector<Tile*>> tiles;

    const float w = static_cast<float>(JSONParser::graphics::GetWidth()) / static_cast<float>(horizontal_tiles);
    const float h = static_cast<float>(JSONParser::graphics::GetHeight()) / static_cast<float>(vertical_tiles);

    std::ifstream map_file;
    std::ifstream hitboxes_file;

    Node* newRoom = new Node();
    newRoom->room = new Room();

    std::string map_filepath = map_path + "base_plane_textures.hhmap";
    std::string hitboxes_filepath = map_path + "hitboxes.hhmap";

    try {
        FileOpener::OpenFileInput(map_file, map_filepath);
        FileOpener::OpenFileInput(hitboxes_file, hitboxes_filepath);
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    newRoom->room->SetFilepath(map_path);

    std::string base_line;
    std::string hitboxes_line;
    int y = 0;

    while (std::getline(map_file, base_line)) {
        std::stringstream base_ss(base_line);
        std::string cell;

        std::vector<Tile*> row;
        int x = 0;

        if (base_line.starts_with("#") || base_line.empty()) {
            continue;
        }

        if (base_line.starts_with('?')) {
            char a;
            int x, y;
            base_ss >> a;
            base_ss >> y;
            base_ss >> x;
            newRoom->room->SetSpawnCoord(x, y);
            continue;
        }

        std::getline(hitboxes_file, hitboxes_line);
        std::stringstream hitboxes_ss(hitboxes_line);

        while (base_ss >> cell) {
            bool hitbox;
            hitboxes_ss >> hitbox;

            Tile* tile = new Tile();

            tile->SetTexture(textureManager->GetTextureByCode(cell));
            tile->SetRect(static_cast<float>(x) * w, static_cast<float>(y) * h, w, h);
            tile->SetHitbox(hitbox);
            row.push_back(tile);

            x++;
        }
        tiles.push_back(row);
        y++;
    }

    newRoom->room->SetTiles(tiles);

    if (spawn_room == nullptr) {
        spawn_room = newRoom;
        current_room = spawn_room;
    } else {
        switch (dir) {

        case DIRECTION::DIR_UP:
            current_room->up = newRoom;
            current_room->up->down = current_room;
            break;

        case DIRECTION::DIR_LEFT:
            current_room->left = newRoom;
            current_room->left->right = current_room;
            break;

        case DIRECTION::DIR_DOWN:
            current_room->down = newRoom;
            current_room->down->up = current_room;
            break;

        case DIRECTION::DIR_RIGHT:
            current_room->right = newRoom;
            current_room->right->left = current_room;
            break;

        case DIRECTION::DIR_NONE:
            current_room = newRoom;
            break;
        }
    }
}

auto RoomManager::GetCurrentRoom() const -> Room* {
    return this->current_room->room;
}

auto RoomManager::GoLeft() -> void {

    if (current_room->left == nullptr) {
        GenerateRoom(DIRECTION::DIR_LEFT, "../maps/room1/");
    }

    current_room = current_room->left;
}

auto RoomManager::GoRight() -> void {
    if (current_room->right == nullptr) {
        GenerateRoom(DIRECTION::DIR_RIGHT, "../maps/room1/");
    }

    current_room = current_room->right;
}

auto RoomManager::GoUp() -> void {

    if (current_room->up == nullptr) {
        GenerateRoom(DIRECTION::DIR_UP, "../maps/room1/");
    }

    current_room = current_room->up;
}

auto RoomManager::GoDown() -> void {
    if (current_room->down == nullptr) {
        GenerateRoom(DIRECTION::DIR_DOWN, "../maps/room1/");
    }

    current_room = current_room->down;
}

auto RoomManager::ResizeRoom() -> void {
    std::vector<std::vector<Tile*>> tiles = this->current_room->room->GetTiles();
    int w, h;
    try {
        w = JSONParser::graphics::GetWidth();
        h = JSONParser::graphics::GetHeight();
    } catch (HerionException::File::FileMalformedException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    for (int x = 0; x < tiles.size(); x++) {
        for (int y = 0; y < tiles[x].size(); y++) {
            float newW, newH;

            newW = static_cast<float>(w) / static_cast<float>(horizontal_tiles);
            newH = static_cast<float>(h) / static_cast<float>(vertical_tiles);

            tiles[x][y]->SetRect(static_cast<float>(y) * newW, static_cast<float>(x) * newH, newW, newH);
        }
    }
}

auto RoomManager::ResizeEditorRoom(Room* room) -> void {
    std::vector<std::vector<Tile*>> tiles = room->GetTiles();

    int w, h;

    try {
        w = JSONParser::graphics::GetWidth();
        h = JSONParser::graphics::GetHeight();
    } catch (HerionException::File::FileMalformedException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    for (int x = 0; x < tiles.size(); x++) {
        for (int y = 0; y < tiles[x].size(); y++) {
            float newW, newH;

            newW = static_cast<float>(w) / static_cast<float>(horizontal_tiles);
            newH = static_cast<float>(h) / static_cast<float>(vertical_tiles);

            tiles[x][y]->SetRect(static_cast<float>(y) * newW, static_cast<float>(x) * newH, newW, newH);
        }
    }
}

auto RoomManager::DrawCurrentRoom(SDL_Renderer* renderer) const -> void {
    current_room->room->Draw(renderer);
}

auto RoomManager::SetDimensions(int screen_width, int screen_height, int horizontal_tiles, int vertical_tiles) -> void {
    this->screen_width = screen_width;
    this->screen_height = screen_height;
    this->horizontal_tiles = horizontal_tiles;
    this->vertical_tiles = vertical_tiles;
}

auto RoomManager::SetTextureManager(TextureManager* texture_manager) -> void {
    this->textureManager = texture_manager;
}

auto RoomManager::GetPlayerSpawnCellX() const -> int {
    return this->current_room->room->GetSpawnX() * (JSONParser::graphics::GetWidth() / this->horizontal_tiles);
}

auto RoomManager::GetPlayerSpawnCellY() const -> int {
    return this->current_room->room->GetSpawnY() * (JSONParser::graphics::GetHeight() / this->vertical_tiles);
}
