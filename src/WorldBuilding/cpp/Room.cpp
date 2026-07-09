//
// Created by david on 17/11/2025.
//

#include "../hpp/Room.hpp"

#include "../../Utils/hpp/JSONParser.hpp"
#include "SDL3/SDL_oldnames.h"
#include "SDL3/SDL_rect.h"

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

void Room::SetTiles(const std::vector<std::vector<Tile*>> &new_tiles) {
    this->tiles = new_tiles;
    this->horizontal_tiles = this->tiles[0].size();
    this->vertical_tiles =  this->tiles.size();

    this->tile_width = width / horizontal_tiles;
    this->tile_height = height / vertical_tiles;
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


int Room::GetHorizontalTiles() {
    return horizontal_tiles;
}

int Room::GetVerticalTiles() {
    return vertical_tiles;
}

void Room::SetFilepath(const std::string &filepath) {
    this->filepath = filepath;
}

void Room::CheckPlayerCollision(Player* player)
{
    player->SetOnGround(false);

    float& px = player->GetPosX();
    float& py = player->GetPosY();

    float& vx = player->GetVelocityX();
    float& vy = player->GetVelocityY();

    SDL_FRect rect = player->player_rect;

    bool grounded = false;

    float bestPenX = 0.0f;
    float bestPenY = 0.0f;
    float bestAbsPen = 0.0f;
    bool resolved = false;

    for (auto& row : tiles)
    {
        for (Tile* t : row)
        {
            if (!t->HasHitbox())
                continue;

            SDL_FRect* b = t->GetRect();

            if (rect.x + rect.w <= b->x || rect.x >= b->x + b->w ||
                rect.y + rect.h <= b->y || rect.y >= b->y + b->h)
                continue;

            float overlapLeft   = (rect.x + rect.w) - b->x;
            float overlapRight  = (b->x + b->w) - rect.x;
            float overlapTop    = (rect.y + rect.h) - b->y;
            float overlapBottom = (b->y + b->h) - rect.y;

            // scegli asse più piccolo
            if (std::min(overlapLeft, overlapRight) < std::min(overlapTop, overlapBottom))
            {
                float pen = (overlapLeft < overlapRight) ? -overlapLeft : overlapRight;

                if (!resolved || std::abs(pen) > std::abs(bestAbsPen))
                {
                    bestAbsPen = pen;
                    bestPenX = pen;
                    bestPenY = 0.0f;
                    resolved = true;
                }
            }
            else
            {
                float pen = (overlapTop < overlapBottom) ? -overlapTop : overlapBottom;

                if (!resolved || std::abs(pen) > std::abs(bestAbsPen))
                {
                    bestAbsPen = pen;
                    bestPenX = 0.0f;
                    bestPenY = pen;
                    resolved = true;
                }
            }
        }
    }

    // applica UNA sola correzione
    if (bestPenX != 0.0f)
    {
        px += bestPenX;
        vx = 0.0f;

        if (bestPenX > 0)
            player->SetAttachedToWallLeft(true);
        else
            player->SetAttachedToWallRight(true);
    }

    if (bestPenY != 0.0f)
    {
        py += bestPenY;
        vy = 0.0f;

        if (bestPenY < 0)
            grounded = true;
    }

    player->SetOnGround(grounded);
}
