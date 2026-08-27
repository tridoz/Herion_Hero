#ifndef HERION_HERO_PLAYER_HPP
#define HERION_HERO_PLAYER_HPP

#include <unordered_map>

#include "../../Exceptions/hpp/HerionFileException.hpp"
#include "../../Utils/hpp/Animation.hpp"
#include "../../Utils/hpp/FileOpener.hpp"
#include "../../Utils/hpp/JSONParser.hpp"
#include "Entity.hpp"

#include "../../Utils/hpp/Logger.hpp"

class TextureManager;

class Player : public Entity {

  public:
    Player();
    ~Player();

    auto SetTextureManager(TextureManager*) -> void;

  private:
    TextureManager* texture_manager;
};

#endif // HERION_HERO_PLAYER_HPP
