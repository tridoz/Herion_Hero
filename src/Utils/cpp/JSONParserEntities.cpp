#include "../hpp/JSONParser.hpp"
#include "HerionFileException.hpp"

auto JSONParser::entities::GetEntityProperties(const std::string& filepath)
    -> std::vector<struct JSONParser::entities::EntityProperties> {
    std::vector<struct JSONParser::entities::EntityProperties> properties{};

    std::ifstream entities_file_stream;
    try {
        FileOpener::OpenFileInput(entities_file_stream, filepath);
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    nlohmann::json entities_file;

    entities_file_stream >> entities_file;

    if (!entities_file.contains("entities")) {
        THROW_FILE_MALFORMED(filepath);
    }

    for (const auto& element : entities_file["entities"]) {

        std::string type = element.at("type").get<std::string>();
        std::string animations_file_path = element.at("animations_file_path").get<std::string>();

        struct JSONParser::entities::EntityStats stats;
        struct JSONParser::entities::EntityPosition position;
        struct JSONParser::entities::EntityCoordinates coordinates;

        stats.hp = element["stats"].at("hp").get<int>();
        stats.mana = element["stats"].at("mana").get<int>();
        stats.stamina = element["stats"].at("stamina").get<int>();

        position.plane = element["position"].at("plane").get<std::string>();

        coordinates.x = element["position"]["coordinates"].at("x").get<float>();
        coordinates.y = element["position"]["coordinates"].at("y").get<float>();

        position.coordinates = coordinates;

        properties.push_back({type, animations_file_path, stats, position});
    }

    return properties;
}

auto JSONParser::entities::GetEntitiTextureFilePath(const std::string& filename, const std::string& entity_name)
    -> std::string {
    std::ifstream entities_file;
    try {
        FileOpener::OpenFileInput(entities_file, filename);
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    nlohmann::json entities_json;
    entities_file >> entities_json;

    for (const auto& entity : entities_json["entities"]) {
        if (entity["name"] == entity_name)
            return entity["texture"];
    }

    return "";
}

auto JSONParser::entities::GetEntityLimit(const std::string& filename, const std::string& entity_name) -> int {
    std::ifstream entities_file;
    try {
        FileOpener::OpenFileInput(entities_file, filename);
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    nlohmann::json entities_json;
    entities_file >> entities_json;

    for (const auto& entity : entities_json["entities"]) {
        if (entity["name"] == entity_name)
            return entity["limit"];
    }

    return 0;
}
