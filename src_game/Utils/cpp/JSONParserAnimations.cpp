//
// Created by trida on 1/5/26.
//

#include "../hpp/JSONParser.hpp"

void JSONParser::animations::SetConfigFile(const std::string &filename) {
	std::ifstream json_file;
	animation_file_path = filename;
	try {
		FileOpener::OpenFileInput( json_file, animation_file_path);
	} catch ( HerionException::File::FileException& ex ) {
		ex.UpdateStackTrace( GET_CONTEXT() );
		throw;
	}

	json_file >> animation_file;

}

int JSONParser::animations::GetAnimationNumbers() {
	if ( !animation_file.contains("animations") ) {
		THROW_FILE_MALFORMED( animation_file_path + "\t=> animations");
	}

	return animation_file["animations"].size();
}

JSONParser::animations::AnimationElementsFields JSONParser::animations::GetAnimationElementsFields(const int num_animation) {

	if (
		!animation_file.contains("animations") ||
		animation_file["animations"].size() < num_animation ||
		!animation_file["animations"][num_animation].contains("path") ||
		!animation_file["animations"][num_animation].contains("name") ||
		!animation_file["animations"][num_animation].contains("frame_number") ||
		!animation_file["animations"][num_animation].contains("frame_to_load")
		)
	{
		THROW_FILE_MALFORMED( animation_file_path + "\t=> " + std::to_string(num_animation) );
	}
	const std::string path = animation_file["animations"][num_animation]["path"];
	const std::string name = animation_file["animations"][num_animation]["name"];
	const int frame_number = animation_file["animations"][num_animation]["frame_number"];
	const int frame_to_load = animation_file["animations"][num_animation]["frame_to_load"];

	return { path, name, frame_number, frame_to_load};

}
