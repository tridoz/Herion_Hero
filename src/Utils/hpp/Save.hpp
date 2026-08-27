//
// Created by trida on 1/2/26.
//

#ifndef HERION_HERO_SAVE_HPP
#define HERION_HERO_SAVE_HPP

#include "../../Entities/hpp/Player.hpp"

class Save {

  private:
    static Player* player;
    static std::string save_file_name;

    typedef struct new_save_values {

    } new_save_values;

  public:
    static auto SetPlayer(Player*) -> void;
    static auto SetSaveFilename(std::string&) -> void;

    static auto LoadSave() -> void;
    static auto CreateSave() -> void;
    static auto SaveGame() -> void;
    static auto DeleteSave() -> void;
};

#endif // HERION_HERO_SAVE_HPP