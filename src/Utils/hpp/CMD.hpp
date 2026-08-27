//
// Created by tridoz on 14/05/26.
//

#ifndef HERION_HERO_CMD_HPP
#define HERION_HERO_CMD_HPP

#include "Logger.hpp"

#include <array>
#include <string>
#include <vector>

class CMD {
  public:
    static auto get_files_and_directories_names(const std::string&) -> std::vector<std::string>;
};

#endif // HERION_HERO_CMD_HPP
