//
// Created by tridoz on 14/05/26.
//

#ifndef HERION_HERO_CMD_HPP
#define HERION_HERO_CMD_HPP

#include "Logger.hpp"

#include <vector>
#include <string>
#include <array>

class CMD {
public:

    static std::vector<std::string> get_files_and_directories_names( const std::string& path );

};


#endif //HERION_HERO_CMD_HPP
