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

	}new_save_values;

public:

	static void SetPlayer( Player* player );
	static void SetSaveFilename( std::string& filename );

	static void LoadSave();
	static void CreateSave();
	static void SaveGame();
	static void DeleteSave();

};


#endif //HERION_HERO_SAVE_HPP