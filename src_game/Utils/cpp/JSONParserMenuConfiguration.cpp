//
// Created by david on 20/12/2025.
//

#include "../hpp/JSONParser.hpp"


void JSONParser::menu_configuration::SetConfigFile(const std::string& filename) {
    config_file_path = "../" + filename;
    std::ifstream json_file;

    try {
        FileOpener::OpenFileInput( json_file,  config_file_path );
    } catch ( HerionException::File::FileException& ex ) {
        ex.UpdateStackTrace( GET_CONTEXT() );
        throw;
    }


    json_file >> config_file;
}


std::string JSONParser::menu_configuration::GetBackgroundImagePath() {
    if ( !config_file.contains("background_path") ) {
        THROW_FILE_MALFORMED( config_file_path + "\t=> background_path" );
    }

    return config_file["background_path"];

}

std::string JSONParser::menu_configuration::GetMenuType() {
    if ( !config_file.contains("menu_type") ) {
        THROW_FILE_MALFORMED( config_file_path + "\t=> menu_type");
    }

    return config_file["menu_type"];
}

std::string JSONParser::menu_configuration::GetCmd() {
    if ( !config_file.contains("cmd") ) {
        THROW_FILE_MALFORMED( config_file_path + "\t=> cmd");
    }

    return config_file["cmd"];
}

int JSONParser::menu_configuration::GetDirectoryTextureSize() {
    if ( !config_file.contains("texture_size_directory") ) {
        THROW_FILE_MALFORMED( config_file_path + "\t=> texture_size_directory");
    }

    return config_file["texture_size_directory"];
}

int JSONParser::menu_configuration::GetFileTextureSize() {
    if ( !config_file.contains("texture_size_file") ) {
        THROW_FILE_MALFORMED( config_file_path + "\t=> texture_size_file");
    }

    return config_file["texture_size_file"];
}


float JSONParser::menu_configuration::GetStartY() {
    if ( !config_file.contains("start_y") ) {
        THROW_FILE_MALFORMED( config_file_path + "\t=> start_y" );
    }

    return config_file["start_y"];
}

float JSONParser::menu_configuration::GetButtonYOffset() {
    if ( !config_file.contains("button_y_offset") ) {
        THROW_FILE_MALFORMED( config_file_path + "\t=> button_y_offset" );
    }
    return config_file["button_y_offset"];
}

float JSONParser::menu_configuration::GetCenterPieceOffset() {
    if (!config_file.contains("center_piece_offset") ) {
        THROW_FILE_MALFORMED( config_file_path + "\t=> center_piece_offset");
    }
    return config_file["center_piece_offset"];
}

int JSONParser::menu_configuration::GetNumRows() {
    if ( !config_file.contains("rows") ) {
        THROW_FILE_MALFORMED( config_file_path + "\t=> rows");
    }
    return config_file["rows"].size();
}

int JSONParser::menu_configuration::GetRowButtonXOffset(int num_row) {
    if (
        !config_file.contains("rows") ||
        config_file["rows"].size() < num_row ||
        !config_file["rows"][num_row].contains("button_x_offset")
        )
    {
        THROW_FILE_MALFORMED( config_file_path + "\t=> rows , n_row: " + std::to_string(num_row) + ", button_x_offset");
    }

    return config_file["rows"][num_row]["button_x_offset"];
}

int JSONParser::menu_configuration::GetRowStartingX(int num_row) {
    if (
        !config_file.contains("rows") ||
        config_file["rows"].size() < num_row ||
        !config_file["rows"][num_row].contains("starting_x")
        )
    {
        THROW_FILE_MALFORMED( config_file_path + "\t=> rows , n_row: " + std::to_string(num_row) + ", starting_x");
    }

    return config_file["rows"][num_row]["starting_x"];
}

int JSONParser::menu_configuration::GetRowNumElements(int num_row) {
    if (
        !config_file.contains("rows") ||
        config_file["rows"].size() < num_row ||
        !config_file["rows"][num_row].contains("elements")
    )
    {
        THROW_FILE_MALFORMED( config_file_path + "\t=> rows , n_row: " + std::to_string(num_row) + ", elements");
    }

    return config_file["rows"][num_row]["elements"].size();
}

JSONParser::menu_configuration::RowElementFields
JSONParser::menu_configuration::GetRowElementFields(int num_row, int num_element)
{

    if (
        !config_file.contains("rows") ||
        config_file["rows"].size() < num_row ||
        !config_file["rows"][num_row].contains("elements") ||
        config_file["rows"][num_row]["elements"].size() < num_element
    )
    {
        THROW_FILE_MALFORMED( config_file_path + "\t=> rows , n_row: " + std::to_string(num_row) + ", button_x_offset, n_elem:" + std::to_string(num_element) );
    }

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










