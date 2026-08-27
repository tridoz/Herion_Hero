//
// Created by tridoz on 20/05/26.
//

#ifndef HERION_HERO_SCROLLPANEMENU_HPP
#define HERION_HERO_SCROLLPANEMENU_HPP

#include "Menu.hpp"

class ScrollPaneMenu : public Menu {

  private:
    struct TextureFile {
        std::string name;
        std::string path;
        Texture* texture;
    };

    struct Directory {
        int depth;
        std::string path;
        std::unordered_map<std::string, Directory*> SubDirectory;
        std::vector<TextureFile> Files;
    };

    Directory* directory;

    auto CreateButtonsAndTexts(Directory*&) -> void;
    auto CreateSubDirectories(Directory*&, const std::string&, int) -> void;

  public:
    auto CheckCollision(const std::vector<SDL_FRect>&, float, float) -> bool override;
    auto LoadConfiguration(const std::string&) -> void override;
    auto Draw(SDL_Renderer*) const -> void override;

    auto GetCollisionButton(float, float) -> Button* override;
};

#endif // HERION_HERO_SCROLLPANEMENU_HPP
