//
// Created by trida on 1/4/26.
//

#ifndef HERION_HERO_FILEOPENER_HPP
#define HERION_HERO_FILEOPENER_HPP

#include "../../Exceptions/hpp/HerionFileException.hpp"
#include "Logger.hpp"
#include <fstream>

class FileOpener {
  private:
    static std::string base_path;

  public:
    static auto OpenFileInput(std::ifstream&, const std::string&) -> void;
    static auto OpenFileOutput(std::ofstream&, const std::string&) -> void;
};

#endif // HERION_HERO_FILEOPENER_HPP
