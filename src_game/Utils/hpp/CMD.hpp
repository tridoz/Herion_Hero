//
// Created by tridoz on 14/05/26.
//

#ifndef HERION_HERO_CMD_HPP
#define HERION_HERO_CMD_HPP

#include <vector>
#include <string>
#include <array>

class CMD {
public:

    static std::vector<std::string> multiline_exec( const std::string& command );
    static std::string exec( const std::string& command );

};


#endif //HERION_HERO_CMD_HPP
