//
// Created by david on 20/12/2025.
//

#include "../hpp/JSONParser.hpp"


void JSONParser::menu_configuration::SetConfigFile(const std::string& config_file_path) {
    std::ifstream json_file;

    try {
        FileOpener::OpenFileInput( json_file, "../" + config_file_path );
    } catch ( HerionException::File::FileException& ex ) {
        ex.UpdateStackTrace( GET_CONTEXT() );
        throw;
    }

    if ( !json_file.is_open() ) {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParserMenuConfiguration",
            "SetConfigFile",
            "Error while opening the file [" + config_file_path + "] for input: " + strerror( errno )
            );
        return;
    }

    json_file >> config_file;
}


std::string JSONParser::menu_configuration::GetBackgroundImagePath() {
    return config_file["background_image_path"];
}

float JSONParser::menu_configuration::GetStartY() {
    return config_file["start_y"];
}

float JSONParser::menu_configuration::GetButtonYOffset() {
    return config_file["button_y_offset"];
}

float JSONParser::menu_configuration::GetCenterPieceOffset() {
    return config_file["center_piece_offset"];
}

int JSONParser::menu_configuration::GetNumRows() {
    return config_file["rows"].size();
}

int JSONParser::menu_configuration::GetRowButtonXOffset(int num_row) {
    return config_file["rows"][num_row]["button_x_offset"];
}

int JSONParser::menu_configuration::GetRowStartingX(int num_row) {
    return config_file["rows"][num_row]["starting_x"];
}

int JSONParser::menu_configuration::GetRowNumElements(int num_row) {
    return config_file["rows"][num_row]["elements"].size();
}

JSONParser::menu_configuration::RowElementFields
JSONParser::menu_configuration::GetRowElementFields(int num_row, int num_element)
{
    const auto& element = config_file["rows"][num_row]["elements"][num_element];

    RowElementFields result;
    result.type = element.at("type").get<std::string>();
    result.text = element.at("text").get<std::string>();
    result.id = element.at("id").get<std::string>();

    if (element.contains("action")) {
        result.action = element.at("action").get<std::string>();
    }

    return result;
}










