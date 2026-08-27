//
// Created by david on 20/12/2025.
//

#include <algorithm>

#include "../hpp/JSONParser.hpp"

// GRAPHICS
auto JSONParser::graphics::IncreaseResolution() -> void {

    std::ifstream graphics_file;

    try {
        FileOpener::OpenFileInput(graphics_file, json_graphics_file_path);
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    nlohmann::json json_graphics;
    graphics_file >> json_graphics;

    int width = 0, height = 0;

    if (!json_graphics.contains("resolution") && !json_graphics["resolution"].contains("width") &&
        !json_graphics["resolution"].contains("height")) {
        THROW_FILE_MALFORMED(json_graphics_file_path + "\t=> resolution, width, height");
    }

    width = json_graphics["resolution"]["width"].get<int>();
    height = json_graphics["resolution"]["height"].get<int>();

    const auto it = std::ranges::find(resolutions, std::make_pair(width, height));
    int index = (it != resolutions.end()) ? (static_cast<int>(it - resolutions.begin())) : -1;

    if (index < 0 || index == resolutions.size() - 1) {
        THROW_FILE_MALFORMED(json_graphics_file_path + "\t=> resolution values don't exists");
    }

    int new_width = resolutions[index + 1].first;
    int new_height = resolutions[index + 1].second;

    json_graphics["resolution"]["width"] = new_width;
    json_graphics["resolution"]["height"] = new_height;

    std::ofstream graphics_file_output;

    try {
        FileOpener::OpenFileOutput(graphics_file_output, json_graphics_file_path);
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    graphics_file_output << json_graphics.dump(4);
    graphics_file_output.close();
    changed = true;
}

auto JSONParser::graphics::DecreaseResolution() -> void {

    std::ifstream graphics_file;

    try {
        FileOpener::OpenFileInput(graphics_file, json_graphics_file_path);
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    nlohmann::json json_graphics;
    graphics_file >> json_graphics;
    graphics_file.close();

    int width = 0, height = 0;
    if (!json_graphics.contains("resolution") && !json_graphics["resolution"].contains("width") &&
        !json_graphics["resolution"].contains("height")) {
        THROW_FILE_MALFORMED(json_graphics_file_path + "\t=> resolution, width, height");
    }

    width = json_graphics["resolution"]["width"].get<int>();
    height = json_graphics["resolution"]["height"].get<int>();

    const auto it = std::ranges::find(resolutions, std::make_pair(width, height));
    int index = (it != resolutions.end()) ? (static_cast<int>(it - resolutions.begin())) : -1;

    if (index <= 0) {
        THROW_FILE_MALFORMED(json_graphics_file_path + "\t=> resolution values don't exists");
    }

    int new_width = resolutions[index - 1].first;
    int new_height = resolutions[index - 1].second;

    json_graphics["resolution"]["width"] = new_width;
    json_graphics["resolution"]["height"] = new_height;

    std::ofstream graphics_file_output;

    try {
        FileOpener::OpenFileOutput(graphics_file_output, json_graphics_file_path);
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    graphics_file_output << json_graphics.dump(4);
    graphics_file_output.close();
    changed = true;
}

auto JSONParser::graphics::GetWidth() -> int {

    std::ifstream graphics_file;

    try {
        FileOpener::OpenFileInput(graphics_file, json_graphics_file_path);
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    nlohmann::json json_graphics;
    graphics_file >> json_graphics;
    graphics_file.close();

    if (!json_graphics.contains("resolution") && !json_graphics["resolution"].contains("width")) {
        THROW_FILE_MALFORMED(json_graphics_file_path + "\t=> resolution, width");
    }

    return json_graphics["resolution"]["width"].get<int>();
}

auto JSONParser::graphics::GetHeight() -> int {
    std::ifstream graphics_file;

    try {
        FileOpener::OpenFileInput(graphics_file, json_graphics_file_path);
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    nlohmann::json json_graphics;
    graphics_file >> json_graphics;
    graphics_file.close();

    if (!json_graphics.contains("resolution") && !json_graphics["resolution"].contains("height")) {
        THROW_FILE_MALFORMED(json_graphics_file_path + "\t=> resolution, height");
    }

    return json_graphics["resolution"]["height"].get<int>();
}

auto JSONParser::graphics::GetScale() -> float {

    std::ifstream graphics_file;

    try {
        FileOpener::OpenFileInput(graphics_file, json_graphics_file_path);
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    nlohmann::json json_graphics;
    graphics_file >> json_graphics;

    int width = 0, height = 0;
    if (!json_graphics.contains("resolution") && !json_graphics["resolution"].contains("width") &&
        !json_graphics["resolution"].contains("height")) {
        THROW_FILE_MALFORMED(json_graphics_file_path + "\t=> resolution, width, height");
    }

    width = json_graphics["resolution"]["width"].get<int>();
    height = json_graphics["resolution"]["height"].get<int>();

    const auto it = std::ranges::find(resolutions, std::make_pair(width, height));
    int index = (it != resolutions.end()) ? (static_cast<int>(it - resolutions.begin())) : -1;

    if (index < 0 || index > resolutions.size() - 1) {
        THROW_FILE_MALFORMED(json_graphics_file_path + "\t=> resolution values don't exists");
    }

    return texture_scales[index];
}

auto JSONParser::graphics::IncreaseFPSLimit() -> void {
    std::ifstream graphics_file;

    try {
        FileOpener::OpenFileInput(graphics_file, json_graphics_file_path);
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    nlohmann::json json_graphics;
    graphics_file >> json_graphics;
    graphics_file.close();

    int frame_rate = 0;

    if (!json_graphics.contains("frame_rate")) {
        THROW_FILE_MALFORMED(json_graphics_file_path + "\t=> frame_rate");
    }

    frame_rate = json_graphics["frame_rate"].get<int>();

    auto it = std::upper_bound(allowedFPS.begin(), allowedFPS.end(), frame_rate);
    if (it != allowedFPS.end()) {
        frame_rate = *it;
    }

    json_graphics["frame_rate"] = frame_rate;

    std::ofstream graphics_file_output;

    try {
        FileOpener::OpenFileOutput(graphics_file_output, json_graphics_file_path);
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    graphics_file_output << json_graphics.dump(4);
    graphics_file_output.close();
    changed = true;
}

auto JSONParser::graphics::DecreaseFPSLimit() -> void {
    std::ifstream graphics_file;

    try {
        FileOpener::OpenFileInput(graphics_file, json_graphics_file_path);
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    nlohmann::json json_graphics;
    graphics_file >> json_graphics;
    graphics_file.close();

    int frame_rate = 0;
    if (!json_graphics.contains("frame_rate")) {
        THROW_FILE_MALFORMED(json_graphics_file_path + "\t=> frame_rate");
    }
    frame_rate = json_graphics["frame_rate"].get<int>();

    auto it = std::lower_bound(allowedFPS.begin(), allowedFPS.end(), frame_rate);
    if (it != allowedFPS.begin()) {
        --it;
        frame_rate = *it;
    }

    json_graphics["frame_rate"] = frame_rate;

    std::ofstream graphics_file_output;
    try {
        FileOpener::OpenFileOutput(graphics_file_output, json_graphics_file_path);
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    graphics_file_output << json_graphics.dump(4);
    graphics_file_output.close();
    changed = true;
}

auto JSONParser::graphics::GetFrameRate() -> int {
    std::ifstream graphics_file;

    try {
        FileOpener::OpenFileInput(graphics_file, json_graphics_file_path);
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    nlohmann::json json_graphics;
    graphics_file >> json_graphics;
    int frame_rate = 0;

    if (!json_graphics.contains("frame_rate")) {
        THROW_FILE_MALFORMED(json_graphics_file_path + "\t=> frame_rate");
    }

    frame_rate = json_graphics["frame_rate"].get<int>();
    return frame_rate;
}

auto JSONParser::graphics::Changed() -> bool {
    return changed;
}

auto JSONParser::graphics::ChangesApplied() -> void {
    changed = false;
}
