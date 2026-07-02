//
// Created by tridoz on 14/05/26.
//

#include "../hpp/CMD.hpp"

#include <filesystem>
#include <vector>
#include <string>


std::vector<std::string> CMD::get_files_and_directories_names( const std::string& path) {
    std::vector<std::string> result;

    if( !std::filesystem::exists(path) || !std::filesystem::is_directory(path) ) {
        return result;
    }

    for( const auto& entry : std::filesystem::directory_iterator(path) ) {
        result.push_back( entry.path().filename().string() );
    }


    return result;
}
