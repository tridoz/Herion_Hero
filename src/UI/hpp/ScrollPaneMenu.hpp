//
// Created by tridoz on 20/05/26.
//

#ifndef HERION_HERO_SCROLLPANEMENU_HPP
#define HERION_HERO_SCROLLPANEMENU_HPP

#include "Menu.hpp"

class ScrollPaneMenu : public Menu{

private:
    /**
    * @struct TextureFile
    * @brief Information about a File
    */
    struct TextureFile {
        /// name of the file
        std::string name;
        /// path of the file
        std::string path;
        /// texture of the file
        Texture* texture;

        static constexpr auto reflect_members() {
            return std::make_tuple(
                Field<TextureFile, std::string>{ "name", &TextureFile::name },
                Field<TextureFile, std::string>{ "path", &TextureFile::path },
                Field<TextureFile, Texture*>{ "texture", &TextureFile::texture }
            );
        }
    };

    /**
     * @struct Directory
     * @brief Directory and subdirectory system
     */
    struct Directory{
        /// depth of the subdirectory with reference to the main folder
        int depth;
        /// path of the subdirectory
        std::string path;

        /// map of all the current folder subdirectories
        std::unordered_map <
            std::string,
            Directory*
        >SubDirectory;

        /// vector for all the current folder Files
        std::vector<TextureFile> Files;

        static constexpr auto reflect_members() {
            return std::make_tuple(
                Field<Directory, int>{ "depth", &Directory::depth },
                Field<Directory, std::string>{ "path", &Directory::path },
                Field<Directory, std::unordered_map<std::string, Directory*>>{ "SubDirectory", &Directory::SubDirectory },
                Field<Directory, std::vector<TextureFile>>{ "Files", &Directory::Files }
            );
        }

    };

    Directory* directory;

    void CreateButtonsAndTexts( Directory*& dir );
    void CreateSubDirectories( Directory*& directory, const std::string& base_directory, int depth );

public:
    bool CheckCollision( std::vector< SDL_FRect >, float x, float y );
    void LoadConfiguration( const std::string& cfg_json_filepath );
    void Draw( SDL_Renderer* renderer ) const;

    Button* GetCollisionButton( float x, float y );

    static constexpr auto reflect_members() {
        return concat_tuple(
            Menu::reflect_members(),
            std::make_tuple(
                Field<ScrollPaneMenu, Directory*>{ "directory", &ScrollPaneMenu::directory }

            )
        );
    }

};


#endif //HERION_HERO_SCROLLPANEMENU_HPP
