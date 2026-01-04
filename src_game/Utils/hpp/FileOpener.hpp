//
// Created by trida on 1/4/26.
//

#ifndef HERION_HERO_FILEOPENER_HPP
#define HERION_HERO_FILEOPENER_HPP


#include "Logger.hpp"
#include "../../Exceptions/hpp/HerionFileException.hpp"

class FileOpener {

public:
	static void OpenFileInput( std::ifstream& in, const std::string& filepath);
	static void OpenFileOutput( std::ofstream& out, const std::string& filepath);

};


#endif //HERION_HERO_FILEOPENER_HPP