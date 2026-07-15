#ifndef HERION_HERO_PLAYER_HPP
#define HERION_HERO_PLAYER_HPP

#include <unordered_map>

#include "../../Exceptions/hpp/HerionFileException.hpp"
#include "../../Utils/hpp/Animation.hpp"
#include "../../Utils/hpp/FileOpener.hpp"
#include "../../Utils/hpp/JSONParser.hpp"
#include "Entity.hpp"

#include "../../Utils/hpp/Logger.hpp"
#include "../../Utils/hpp/Reflector.hpp"

class TextureManager;

class Player : public Entity {

  public:
    Player();
    ~Player();

    void SetTextureManager(TextureManager* new_texture_manager);

    static constexpr auto reflect_members() {
        return std::make_tuple(
            Field<Player, TextureManager*>{.name = "texture_manager", .ptr = &Player::texture_manager}
        );
    }

  private:
    TextureManager* texture_manager;
};

#endif // HERION_HERO_PLAYER_HPP
