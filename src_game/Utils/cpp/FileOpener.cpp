//
// Created by trida on 1/4/26.
//

#include "../hpp/FileOpener.hpp"

#include <filesystem>


void FileOpener::OpenFileInput(std::ifstream& in, const std::string& filepath)
{
	in.open(filepath, std::ios::in);

	if (!in.is_open()) {
		if (!std::filesystem::exists(filepath)) {
			THROW_FILE_NOT_FOUND(filepath);
		} else {
			THROW_FILE_OPEN(filepath);
		}
	}

	in.exceptions(std::ifstream::badbit);
}

