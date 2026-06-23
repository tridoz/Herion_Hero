//
// Created by trida on 1/4/26.
//

#ifndef HERION_HERO_FILEOPENER_HPP
#define HERION_HERO_FILEOPENER_HPP


#include "Logger.hpp"
#include "../../Exceptions/hpp/HerionFileException.hpp"
#include <fstream>

class FileOpener {
private:

    static std::string base_path;

public:


    /**
	 * @brief Open file for input
	 * @param in std::ifstream& reference to open
	 * @param filepath Filepath of the file to open
	 */
	static void OpenFileInput( std::ifstream& in, const std::string& filepath);


	/**
	 * @brief Open file for output
	 * @param out std::ofstream reference to open
	 * @param filepath Filepath of the file to open
	 */
	static void OpenFileOutput( std::ofstream& out, const std::string& filepath);

};


#endif //HERION_HERO_FILEOPENER_HPP
