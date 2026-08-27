//
// Created by tridoz on 20/05/26.
//

#include "../hpp/EditorRoom.hpp"

EditorRoom::EditorRoom() {
    this->draw_axis = true;
    this->draw_hitboxes = false;
    this->width = JSONParser::graphics::GetWidth();
    this->height = JSONParser::graphics::GetHeight();
    this->current_editor_texture = nullptr;
}

EditorRoom::~EditorRoom() {
    SDL_DestroyTexture(current_editor_texture->GetTexture());
    delete current_editor_texture;
    current_editor_texture = nullptr;

    for (auto& [name, btns] : buttons) {
        for (Button* b : btns) {
            delete b;
            b = nullptr;
        }
    }

    for (ForegroundElement* fe : foreground_elements) {
        delete fe;
        fe = nullptr;
    }

    for (BackgroundElement* be : background_elements) {
        delete be;
        be = nullptr;
    }
}

auto EditorRoom::DrawAxis(SDL_Renderer* renderer) const -> void {

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i <= horizontal_tiles; ++i) {
        SDL_RenderLine(
            renderer,
            static_cast<float>(i) * tile_width,
            0,
            static_cast<float>(i) * tile_width,
            static_cast<float>(height)
        );
    }

    for (int i = 0; i <= vertical_tiles; ++i) {
        SDL_RenderLine(
            renderer,
            0,
            static_cast<float>(i) * tile_height,
            static_cast<float>(width),
            static_cast<float>(i) * tile_height
        );
    }
}

auto EditorRoom::SetHitboxes() -> void {

    for (auto& tile : tiles) {
        std::vector<bool> row;
        for (auto& i : tile) {
            bool hitbox = i->HasHitbox();
            row.push_back(hitbox);
        }
        hitboxes.push_back(row);
    }
}

auto EditorRoom::UpdateHitbox(int cell_x, int cell_y) -> void {
    this->hitboxes[cell_y][cell_x] = !this->hitboxes[cell_y][cell_x];
}

auto EditorRoom::DrawHitboxes(SDL_Renderer* renderer) const -> void {

    for (size_t j = 0; j < hitboxes.size(); ++j) {
        for (size_t i = 0; i < hitboxes[j].size(); ++i) {
            bool hitbox = hitboxes[j][i];

            if (hitbox) {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

                SDL_FRect rect;
                rect.x = static_cast<float>(i) * tile_width;
                rect.y = static_cast<float>(j) * tile_height;
                rect.w = tile_width;
                rect.h = tile_height;

                SDL_RenderRect(renderer, &rect);
            }
        }
    }
}

auto EditorRoom::Draw(SDL_Renderer* r) -> void {
    for (std::vector<Tile*>& tiles_row : tiles) {
        for (Tile*& tile : tiles_row) {
            tile->Draw(r);
        }
    }

    for (const auto& [name, btns] : buttons) {
        for (Button* b : btns) {
            b->Draw(r);
        }
    }
}

auto EditorRoom::SetCurrentEditorTexture(Texture* texture) -> void {
    this->current_editor_texture = texture;
}

auto EditorRoom::GetCurrentEditorTexture() -> Texture* {
    return current_editor_texture;
}

auto EditorRoom::AppendToFile(const std::string& row, std::vector<std::string>& vect) -> void {
    vect.push_back(row);
}

auto EditorRoom::SaveNewEditConfiguration() -> void {

    for (const auto& row : tiles) {
        std::string str_row;
        for (const auto& tile : row) {
            str_row += tile->GetCode() + " ";
        }
        AppendToFile(str_row, this->base_plan_output_file);
    }

    for (const auto& row : hitboxes) {
        std::string str_row;
        for (bool hitbox : row) {
            str_row += std::to_string(hitbox) + " ";
        }
        AppendToFile(str_row, this->hitboxes_output_file);
    }

    std::ofstream base_place_output_file_stream;
    std::ofstream hitbox_output_file_stream;

    try {
        FileOpener::OpenFileOutput(base_place_output_file_stream, filepath + "base_plane_textures.hhmap");
        FileOpener::OpenFileOutput(hitbox_output_file_stream, filepath + "hitboxes.hhmap");
    } catch (HerionException::File::FileException& ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        throw;
    }

    for (const auto& line : base_plan_output_file) {
        base_place_output_file_stream << line << '\n';
    }

    for (const auto& line : hitboxes_output_file) {
        hitbox_output_file_stream << line << '\n';
    }

    this->base_plan_output_file.erase(base_plan_output_file.begin() + 2, base_plan_output_file.end());
    this->hitboxes_output_file.clear();
}

auto EditorRoom::ToggleAxis() -> void {
    draw_axis = !draw_axis;
}

auto EditorRoom::ShouldDrawAxis() const -> bool {
    return draw_axis;
}

auto EditorRoom::ToggleHitboxes() -> void {
    draw_hitboxes = !draw_hitboxes;
}

auto EditorRoom::ShouldDrawHitboxes() const -> bool {
    return draw_hitboxes;
}

auto EditorRoom::SetAction(const std::string& action) -> void {
    this->action = action;
}

auto EditorRoom::GetAction() const -> std::string {
    return this->action;
}

auto EditorRoom::SetCurrentEntityToSet(const std::string& entity) -> void {
    this->current_entity_to_set = entity;
}

auto EditorRoom::GetCurrentEntity() const -> std::string {
    return this->current_entity_to_set;
}

auto EditorRoom::GetBackgroundVector() -> std::vector<std::string>& {
    return this->background_output_file;
}

auto EditorRoom::GetForegroundVector() -> std::vector<std::string>& {
    return this->foreground_output_file;
}

auto EditorRoom::GetBasePlaneVector() -> std::vector<std::string>& {
    return this->base_plan_output_file;
}

auto EditorRoom::AddButton(Button* btn, std::string name) -> void {
    if (this->buttons.contains(name)) {
        this->buttons.at(name).emplace_back(btn);
    } else {
        std::vector<Button*> b{btn};
        this->buttons.emplace(name, b);
    }
}

auto EditorRoom::GetEntitiCount(const std::string& name) const -> int {
    return this->buttons.contains(name) ? static_cast<int>(this->buttons.at(name).size()) : 0;
}
