//
// Created by david on 20/12/2025.
//


#include "../hpp/JSONParser.hpp"


//GRAPHICS
void JSONParser::graphics::IncreaseResolution() {

    std::ifstream graphics_file( json_graphics_file_path, std::ios::in );
    if ( !graphics_file.is_open() ) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::graphics",
            "IncreaseResolution",
            "Error while opening file [" + json_graphics_file_path + "] for input : " + strerror( errno )
            );
        return;
    }

    nlohmann::json json_graphics;
    graphics_file >> json_graphics;

    int width = 0, height = 0;
    if (json_graphics.contains("resolution") &&
        json_graphics["resolution"].contains("width") &&
        json_graphics["resolution"].contains("height"))
    {
        width = json_graphics["resolution"]["width"].get<int>();
        height = json_graphics["resolution"]["height"].get<int>();
    } else {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::graphics",
            "IncreaseResolution",
            "Error while parsing file [" + json_graphics_file_path + "] for output : resolutions {width: height} doesn't exist"
            );
        return;
    }

    const auto it = std::find(resolutions.begin(), resolutions.end(),
                        std::make_pair(width, height));
    int index = (it != resolutions.end()) ? (it - resolutions.begin()) : -1;

    if (index < 0 || index == resolutions.size() - 1) {
        return;
    }

    int new_width = resolutions[index + 1].first;
    int new_height = resolutions[index + 1].second;

    json_graphics["resolution"]["width"] = new_width;
    json_graphics["resolution"]["height"] = new_height;

    std::ofstream graphics_file_output( json_graphics_file_path , std::ios::out );
    if ( !graphics_file_output.is_open() ) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::graphics",
            "IncreaseResolution",
            "Error while opening file [" + json_graphics_file_path + "] for input : " + strerror( errno )
        );
        return;
    }

    graphics_file_output << json_graphics.dump(4);
    graphics_file_output.close();
    changed = true;
}

void JSONParser::graphics::DecreaseResolution() {

    std::ifstream graphics_file(json_graphics_file_path, std::ios::in);
    if (!graphics_file.is_open()) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::graphics",
            "DecreaseResolution",
            "Error while opening file [" + json_graphics_file_path + "] for input : " + strerror(errno)
        );
        return;
    }

    nlohmann::json json_graphics;
    graphics_file >> json_graphics;
    graphics_file.close();

    int width = 0, height = 0;
    if (json_graphics.contains("resolution") &&
        json_graphics["resolution"].contains("width") &&
        json_graphics["resolution"].contains("height"))
    {
        width = json_graphics["resolution"]["width"].get<int>();
        height = json_graphics["resolution"]["height"].get<int>();
    } else {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::graphics",
            "DecreaseResolution",
            "Error while parsing file [" + json_graphics_file_path + "] for output : resolutions {width: height} doesn't exist"
        );
        return;
    }

    const auto it = std::find(resolutions.begin(), resolutions.end(),
                              std::make_pair(width, height));
    int index = (it != resolutions.end()) ? (it - resolutions.begin()) : -1;

    if (index <= 0) {
        return;
    }

    int new_width = resolutions[index - 1].first;
    int new_height = resolutions[index - 1].second;

    json_graphics["resolution"]["width"] = new_width;
    json_graphics["resolution"]["height"] = new_height;

    std::ofstream graphics_file_output(json_graphics_file_path, std::ios::out);
    if (!graphics_file_output.is_open()) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::graphics",
            "DecreaseResolution",
            "Error while opening file [" + json_graphics_file_path + "] for output : " + strerror(errno)
        );
        return;
    }

    graphics_file_output << json_graphics.dump(4);
    graphics_file_output.close();
    changed = true;

}

int JSONParser::graphics::GetWidth() {

    std::ifstream graphics_file(json_graphics_file_path, std::ios::in);
    if (!graphics_file.is_open()) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::graphics",
            "GetWidth",
            "Error while opening file [" + json_graphics_file_path + "] for input : " + strerror(errno)
        );
        return 0;
    }

    nlohmann::json json_graphics;
    graphics_file >> json_graphics;
    graphics_file.close();

    if (json_graphics.contains("resolution") &&
        json_graphics["resolution"].contains("width"))
    {
        return json_graphics["resolution"]["width"].get<int>();
    } else {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::graphics",
            "GetWidth",
            "Resolution width not found in file [" + json_graphics_file_path + "]"
        );
        return 0;
    }
}

int JSONParser::graphics::GetHeight() {
    std::ifstream graphics_file(json_graphics_file_path, std::ios::in);
    if (!graphics_file.is_open()) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::graphics",
            "GetHeight",
            "Error while opening file [" + json_graphics_file_path + "] for input : " + strerror(errno)
        );
        return 0;
    }

    nlohmann::json json_graphics;
    graphics_file >> json_graphics;
    graphics_file.close();

    if (json_graphics.contains("resolution") &&
        json_graphics["resolution"].contains("height"))
    {
        return json_graphics["resolution"]["height"].get<int>();
    } else {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::graphics",
            "GetHeight",
            "Resolution height not found in file [" + json_graphics_file_path + "]"
        );
        return 0;
    }
}

float JSONParser::graphics::GetScale() {
    std::ifstream graphics_file( json_graphics_file_path, std::ios::in );
    if ( !graphics_file.is_open() ) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::graphics",
            "GetScale",
            "Error while opening file [" + json_graphics_file_path + "] for input : " + strerror( errno )
            );
        return 0;
    }

    nlohmann::json json_graphics;
    graphics_file >> json_graphics;

    int width = 0, height = 0;
    if (json_graphics.contains("resolution") &&
        json_graphics["resolution"].contains("width") &&
        json_graphics["resolution"].contains("height"))
    {
        width = json_graphics["resolution"]["width"].get<int>();
        height = json_graphics["resolution"]["height"].get<int>();
    } else {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::graphics",
            "GetScale",
            "Error while parsing file [" + json_graphics_file_path + "] for output : resolutions {width: height} doesn't exist"
            );
        return 0;
    }

    const auto it = std::find(resolutions.begin(), resolutions.end(),
                        std::make_pair(width, height));
    int index = (it != resolutions.end()) ? (it - resolutions.begin()) : -1;

    if (index < 0 || index > resolutions.size() - 1) {
        return 0;
    }

    return texture_scales[index];

}

void JSONParser::graphics::IncreaseFPSLimit() {
    std::ifstream graphics_file(json_graphics_file_path, std::ios::in);
    if (!graphics_file.is_open()) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::graphics",
            "IncreaseFPSLimit",
            "Error while opening file [" + json_graphics_file_path + "] for input : " + strerror(errno)
        );
        return;
    }

    nlohmann::json json_graphics;
    graphics_file >> json_graphics;
    graphics_file.close();

    int frame_rate = 0;
    if (json_graphics.contains("frame_rate")) {
        frame_rate = json_graphics["frame_rate"].get<int>();
    } else {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::graphics",
            "IncreaseFPSLimit",
            "frame_rate doesn't exist in file"
        );
        return;
    }

    auto it = std::upper_bound(allowedFPS.begin(), allowedFPS.end(), frame_rate);
    if (it != allowedFPS.end()) {
        frame_rate = *it;
    }

    json_graphics["frame_rate"] = frame_rate;

    std::ofstream graphics_file_output(json_graphics_file_path, std::ios::out);
    if (!graphics_file_output.is_open()) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::graphics",
            "IncreaseFPSLimit",
            "Error while opening file for output: " + std::string(strerror(errno))
        );
        return;
    }

    graphics_file_output << json_graphics.dump(4);
    graphics_file_output.close();
    changed = true;
}

void JSONParser::graphics::DecreaseFPSLimit() {
    std::ifstream graphics_file(json_graphics_file_path, std::ios::in);
    if (!graphics_file.is_open()) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::graphics",
            "DecreaseFPSLimit",
            "Error while opening file [" + json_graphics_file_path + "] for input : " + strerror(errno)
        );
        return;
    }

    nlohmann::json json_graphics;
    graphics_file >> json_graphics;
    graphics_file.close();

    int frame_rate = 0;
    if (json_graphics.contains("frame_rate")) {
        frame_rate = json_graphics["frame_rate"].get<int>();
    } else {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::graphics",
            "DecreaseFPSLimit",
            "frame_rate doesn't exist in file"
        );
        return;
    }

    auto it = std::lower_bound(allowedFPS.begin(), allowedFPS.end(), frame_rate);
    if (it != allowedFPS.begin()) {
        --it;
        frame_rate = *it;
    }

    json_graphics["frame_rate"] = frame_rate;

    std::ofstream graphics_file_output(json_graphics_file_path, std::ios::out);
    if (!graphics_file_output.is_open()) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::graphics",
            "DecreaseFPSLimit",
            "Error while opening file for output: " + std::string(strerror(errno))
        );
        return;
    }

    graphics_file_output << json_graphics.dump(4);
    graphics_file_output.close();
    changed = true;
}

int JSONParser::graphics::GetFrameRate() {
    std::ifstream graphics_file( json_graphics_file_path, std::ios::in );
    if ( !graphics_file.is_open() ) {
        Logger::LogErr(
            std::time(nullptr),
            "OPENING",
            "JSONParser::graphics",
            "GetFrameRate",
            "Error while opening file [" + json_graphics_file_path + "] for input : " + strerror( errno  )
            );
        return -1;
    }

    nlohmann::json json_graphics;
    graphics_file >> json_graphics;
    int frame_rate = 0;

    if ( !json_graphics.contains("frame_rate") ) {
        Logger::LogErr(
            std::time(nullptr),
            "PARSING",
            "JSONParser::graphics",
            "GetFrameRate",
            "File [" + json_graphics_file_path + "] is malformed"
            );
        return -1;
    }

    frame_rate = json_graphics["frame_rate"].get<int>();
    return frame_rate;
}

bool JSONParser::graphics::Changed() {
    return changed;
}

void JSONParser::graphics::ChangesApplied() {
    changed = false;
}
