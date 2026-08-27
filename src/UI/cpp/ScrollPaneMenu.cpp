//
// Created by tridoz on 20/05/26.
//

#include "../hpp/ScrollPaneMenu.hpp"
#include "Renderable.hpp"

auto ScrollPaneMenu::LoadConfiguration(const std::string& cfg_json_filepath) -> void {

    this->filepath = cfg_json_filepath;

    try {
        JSONParser::menu_configuration::SetConfigFile(cfg_json_filepath);
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    std::string cmd;

    this->background_filepath = JSONParser::menu_configuration::GetBackgroundImagePath();
    this->background = this->texture_manager->GetTextureByName(this->background_filepath);

    auto w = static_cast<float>(JSONParser::graphics::GetWidth());
    auto h = static_cast<float>(JSONParser::graphics::GetHeight());

    this->background_rect = {.x = 0, .y = 0, .w = w, .h = h};

    try {
        this->scale = JSONParser::graphics::GetScale();
        cmd = JSONParser::menu_configuration::GetCmd();
    } catch (HerionException::File::FileMalformedException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    if (cmd == "select_all_directory") {
        std::string base_directory = "Assets/WorldBuilding/";
        CreateSubDirectories(this->directory, base_directory, 0);
        this->buttons.clear();
        this->texts.clear();
        CreateButtonsAndTexts(this->directory);
    } else if (cmd == "select_all_entities") {
        std::string base_directory = "src_game/Entities/cpp/";
        CreateSubDirectories(this->directory, base_directory, 0);
        this->button_style.clear();
        this->texts.clear();
        CreateButtonsAndTexts(this->directory);
    }
}

auto ScrollPaneMenu::CheckCollision(const std::vector<SDL_FRect>& buttons, float x, float y) -> bool {
    for (const SDL_FRect& button : buttons) {
        if (x >= button.x && x <= button.x + button.w && y >= button.y + mouse_offset &&
            y <= button.y + mouse_offset + button.h) {
            return true;
        }
    }
    return false;
}

auto ScrollPaneMenu::GetCollisionButton(float x, float y) -> Button* {
    for (const auto& [id, btn] : this->buttons) {
        if (CheckCollision(btn->GetRects(), x, y)) {
            return btn;
        }
    }

    return nullptr;
}

auto ScrollPaneMenu::Draw(SDL_Renderer* renderer) const -> void {

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderTexture(renderer, background->GetTexture(), nullptr, &background_rect);

    for (const auto& [id, button] : buttons) {
        button->DrawWithOffset(renderer, mouse_offset, 0);
    }

    for (const auto& [id, text] : texts) {
        text->DrawWithOffset(renderer, mouse_offset, 0);
    }
}

auto ScrollPaneMenu::CreateButtonsAndTexts(Directory*& dir) -> void {

    const int texture_size_file = JSONParser::menu_configuration::GetFileTextureSize();
    const int texture_size_directory = JSONParser::menu_configuration::GetDirectoryTextureSize();
    const int diff = texture_size_directory - texture_size_file;

    if (dir->SubDirectory.size() == 0) {
        // DRAW FILES

        for (auto& [name, path, texture] : dir->Files) {

            const int depth = dir->depth;
            const int previous_element_already_drawn = static_cast<int>(texts.size() + buttons.size());

            std::vector<Renderable*> renderables;

            SDL_FRect file_rect = {
                .x = static_cast<float>((texture_size_directory * depth) + (texture_size_directory)),
                .y = static_cast<float>(
                    (static_cast<float>(previous_element_already_drawn) * static_cast<float>(texture_size_directory) +
                     static_cast<float>(texture_size_directory) * scale *
                         static_cast<float>(previous_element_already_drawn))
                ),
                .w = static_cast<float>(texture_size_directory) * scale,
                .h = static_cast<float>(texture_size_directory) * scale
            };

            renderables.emplace_back(new Renderable(texture, new SDL_FRect{file_rect}));

            for (int i = 0; i < name.size(); i++) {
                char c = name[i];

                Texture* char_tex = nullptr;
                try {

                    if (std::isupper(c))
                        char_tex = texture_manager->GetTextureByName(
                            "Assets/Font/Editor/UppercaseLetters/" + std::string(1, c) + ".png"
                        );
                    else if (std::islower(c))
                        char_tex = texture_manager->GetTextureByName(
                            "Assets/Font/Editor/LowercaseLetters/" + std::string(1, c) + ".png"
                        );
                    else if (std::isdigit(c))
                        char_tex = texture_manager->GetTextureByName(
                            "Assets/Font/Editor/Numbers/" + std::string(1, c) + ".png"
                        );
                    else if (isspecial(c))
                        char_tex = texture_manager->GetTextureByName(
                            "Assets/Font/Editor/SpecialCharacters/" + GetNameOfSpecialChar(c) + ".png"
                        );
                    else if (isspace(c))
                        char_tex = texture_manager->GetTextureByName("Assets/Font/Editor/SpecialCharacters/space.png");

                } catch (HerionException::File::FileNotFoundException& ex) {
                    ex.UpdateStackTrace(GET_CONTEXT());
                    throw;
                }

                SDL_FRect char_rect = {
                    .x = static_cast<float>((depth * texture_size_file) + (texture_size_file * (i + 2))),
                    .y = static_cast<float>(
                        (static_cast<float>(previous_element_already_drawn) * static_cast<float>(texture_size_file) +
                         static_cast<float>(texture_size_file) * scale *
                             static_cast<float>(previous_element_already_drawn) +
                         static_cast<float>(diff) * scale * static_cast<float>(previous_element_already_drawn))
                    ),
                    .w = static_cast<float>(texture_size_directory) * scale,
                    .h = static_cast<float>(texture_size_directory) * scale
                };

                renderables.emplace_back(new Renderable(char_tex, new SDL_FRect{char_rect}));
            }

            Button* btn = new Button();
            btn->SetText(path);

            btn->SetOnClickReturn([btn]() { return btn->GetText(); });

            btn->SetRenderables(renderables);
            buttons.emplace(path, btn);
        }
        return;
    }

    for (auto& [name, dir] : dir->SubDirectory) {

        const int depth = dir->depth;
        const std::string path = dir->path;
        const int previous_element_already_drawn = static_cast<int>(texts.size() + buttons.size());

        std::vector<Renderable*> renderables;

        Texture* folder_txt = texture_manager->GetTextureByName("Assets/Ui/Editor/Folder.png");
        SDL_FRect folder_rect = {
            .x = static_cast<float>((texture_size_directory * depth)),
            .y = static_cast<float>((
                static_cast<float>(previous_element_already_drawn) * static_cast<float>(texture_size_directory) +
                static_cast<float>(texture_size_directory) * scale * static_cast<float>(previous_element_already_drawn)
            )),
            .w = static_cast<float>(texture_size_directory) * scale,
            .h = static_cast<float>(texture_size_directory) * scale
        };

        renderables.emplace_back(new Renderable(folder_txt, new SDL_FRect{folder_rect}));

        // DRAWING

        for (int i = 0; i < name.size(); i++) {
            char c = name[i];
            Texture* char_tex = nullptr;

            try {

                if (std::isupper(c))
                    char_tex = texture_manager->GetTextureByName(
                        "Assets/Font/Editor/UppercaseLetters/" + std::string(1, c) + ".png"
                    );
                else if (std::islower(c))
                    char_tex = texture_manager->GetTextureByName(
                        "Assets/Font/Editor/LowercaseLetters/" + std::string(1, c) + ".png"
                    );
                else if (std::isdigit(c))
                    char_tex =
                        texture_manager->GetTextureByName("Assets/Font/Editor/Numbers/" + std::string(1, c) + ".png");
                else if (isspecial(c))
                    char_tex = texture_manager->GetTextureByName(
                        "Assets/Font/Editor/SpecialCharacters/" + GetNameOfSpecialChar(c) + ".png"
                    );
                else if (isspace(c))
                    char_tex = texture_manager->GetTextureByName("Assets/Font/Editor/SpecialCharacters/space.png");

            } catch (HerionException::File::FileNotFoundException& ex) {
                ex.UpdateStackTrace(GET_CONTEXT());
                throw;
            }

            SDL_FRect char_rect = {
                .x = static_cast<float>((texture_size_directory * depth) + (texture_size_directory * (i + 1))),
                .y = static_cast<float>(
                    (static_cast<float>(previous_element_already_drawn) * static_cast<float>(texture_size_directory) +
                     static_cast<float>(texture_size_directory) * scale *
                         static_cast<float>(previous_element_already_drawn))
                ),
                .w = static_cast<float>(texture_size_directory) * scale,
                .h = static_cast<float>(texture_size_directory) * scale
            };

            renderables.emplace_back(new Renderable(char_tex, new SDL_FRect{char_rect}));
        }

        Text* txt = new Text();
        txt->SetRenderables(renderables);
        texts.emplace(path, txt);

        CreateButtonsAndTexts(dir);
    }
}

auto ScrollPaneMenu::CreateSubDirectories(Directory*& directory, const std::string& base_directory, int depth) -> void {

    std::vector<std::string> cmd_output = CMD::get_files_and_directories_names(base_directory);

    if (directory == nullptr) {
        directory = new Directory(depth, {}, {});
    }

    if (cmd_output.size() == 0) {
        return;
    }

    for (const auto& output_line : cmd_output) {

        Directory* dir = new Directory(depth + 1, {}, {}, {});

        if (!output_line.contains(".png") && !output_line.contains(".txt") && !output_line.contains(".cpp")) {

            directory->SubDirectory.emplace(std::make_pair(output_line, dir));
            dir->path = base_directory + output_line + "/";
            CreateSubDirectories(dir, base_directory + output_line + "/", depth + 1);

        } else if (output_line.contains(".png")) {

            std::string file_name = base_directory + output_line;
            directory->Files.emplace_back(
                output_line, base_directory + output_line, this->texture_manager->GetTextureByName(file_name)
            );

        } else if (output_line.contains(".cpp")) {
            auto txt = new Texture();
            directory->Files.emplace_back(output_line, base_directory + output_line, txt);
            ;
        }
    }
}
