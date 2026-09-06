
#include "../../Exceptions/hpp/HerionFileException.hpp"
#include "../../Textures/hpp/TextureManager.hpp"
#include "Renderable.hpp"

class Font {
  private:
    static TextureManager* texture_manager;
    static auto isspecial(char c) -> bool;
    static auto GetNameOfSpecialChar(char c) -> std::string;

  public:
    struct FontOptions {
        float texture_size_file;
        float texture_size_directory;
        float diff;
        float scale;
        int depth;
        int previous_element_already_drawn;
    };

    static auto CreateText(const std::string&, struct FontOptions) -> std::vector<Renderable*>;
    static auto SetTextureManager(TextureManager*) -> void;
};