#include "../hpp/Font.hpp"

TextureManager* Font::texture_manager = nullptr;

auto Font::SetTextureManager(TextureManager* mng) -> void {
    Font::texture_manager = mng;
}

auto Font::CreateText(const std::string& text, struct FontOptions opt) -> std::vector<Renderable*> {
    std::vector<Renderable*> renderables;

    for (int i = 0; i < text.size(); i++) {
        char c = text[i];

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
            .x = static_cast<float>((opt.depth * opt.texture_size_file) + (opt.texture_size_file * (i + 2))),
            .y = static_cast<float>(
                (static_cast<float>(opt.previous_element_already_drawn) * static_cast<float>(opt.texture_size_file) +
                 static_cast<float>(opt.texture_size_file) * opt.scale *
                     static_cast<float>(opt.previous_element_already_drawn) +
                 static_cast<float>(opt.diff) * opt.scale * static_cast<float>(opt.previous_element_already_drawn))
            ),
            .w = static_cast<float>(opt.texture_size_directory) * opt.scale,
            .h = static_cast<float>(opt.texture_size_directory) * opt.scale
        };

        renderables.emplace_back(new Renderable(char_tex, new SDL_FRect{char_rect}));
    }

    return renderables;
}

auto Font::isspecial(const char c) -> bool {

    std::vector<char> special_characters = {
        '+', '-', '*', '/', '%', '&', '|', '^', '!', '=', '<', '>', '?', '~', '@', '#', '$', '_', '.'
    };

    return std::find(special_characters.begin(), special_characters.end(), c) != special_characters.end();
}

auto Font::GetNameOfSpecialChar(const char c) -> std::string {

    static const std::unordered_map<char, std::string> charNames = {
        {'+', "plus"},
        {'-', "minus"},
        {'*', "asterisk"},
        {'/', "slash"},
        {'%', "percent"},
        {'&', "ampersand"},
        {'|', "pipe"},
        {'^', "caret"},
        {'!', "exclamation"},
        {'=', "equals"},
        {'<', "less_than"},
        {'>', "greater_than"},
        {'?', "question"},
        {'~', "tilde"},
        {'@', "at"},
        {'#', "hash"},
        {'$', "dollar"},
        {'_', "underscore"},
        {'.', "dot"}
    };

    auto it = charNames.find(c);
    if (it != charNames.end()) {
        return it->second; // Restituisce il nome se trovato
    } else {
        return "Unknown"; // Restituisce "Unknown" se non è un carattere speciale
    }
}