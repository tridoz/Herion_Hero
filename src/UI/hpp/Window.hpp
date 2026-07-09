#ifndef HERION_HERO_WINDOW_HPP
#define HERION_HERO_WINDOW_HPP

//SDL3 INCLUDES
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>


//STD INCLUDES
#include <string>


//CUSTOM INCLUDES
#include <random>

#include "Menu.hpp"
#include "../../Utils/hpp/Logger.hpp"
#include "../../Utils/hpp/COLORS.hpp"
#include "../../Utils/hpp/JSONParser.hpp"

class Window {

private:

    int flags;
    int is_open;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    std::unordered_map< std::string, Menu* > menus;
    Menu* current_menu;

    std::unordered_map<std::string, SDL_Cursor* > Cursors;
    std::string current_cursor_name;

    int width, height;

public:

    Window();
    Window( const std::string& title);
    Window( const std::string& title, int width, int height);

    ~Window();

    /**
     * @brief Return a pointer to the Window's renderer
     * @return SDL_Renderer*
     */
    [[nodiscard]] SDL_Renderer* GetRenderer() const;

    /**
     * @brief Return a pointer to the Window's window
     * @return SDL_Window*
     */
    [[nodiscard]] SDL_Window* GetWindow() const;

    /**
     * @brief Clear the renderer
     */
    void Clear() const;

    /**
     * @brief Set the color used to draw
     */
    void SetColor( COLORS::Color ) const;

    /**
     * @brief Renderer the content of the Window
     */
    void Present() const ;

    /**
     * @brief Resize the Window
     */
    void Resize();

    /**
     * @brief Return the Window's width
     * @return int
     */
    [[nodiscard]] int GetWidth() const;

    /**
     * @brief Return the Window's height
     * @return int
     */
    [[nodiscard]] int GetHeight() const;

    /**
     * @brief Wait a certain amount of time
     */
    void Sleep() const;

    /**
     * @brief Load all the cursors from a given file
     * @param cursor_filepath Filepath to the .txt file containing all the cursors path
     */
    void LoadCursors(const std::string & cursor_filepath);

    /**
     * @brief Set a new cursor
     * @param cursor_name Name of the cursor to set as current
     */
    void SetCursor( const std::string& cursor_name);

    /**
     * @brief Return a pointer to the current cursor
     * @return SDL_Cursor*
     */
    SDL_Cursor* GetCursor();

    /**
     * @brief Return if the Window is being shown or not
     * @return bool
     */
    bool IsOpen() const;

    /**
     * @brief Set the Window as "to show"
     */
    void Show();

    /**
     * @brief Set the Window as "to hide"
     */
    void Hide();

    /**
     * @brief Set a new menu inside the std::unordered_map < std::string, Menu* > menus fields
     * @param name Name of the new menu
     * @param menu_to_set Pointer to the new menu
     */
    void SetMenu( const std::string& name, Menu* menu_to_set );

    /**
     * @brief Set current menu that is being drawn
     * @param name Menu name
     */
    void SetCurrentMenu( const std::string& name);

    /**
     * @brief Return a pointer a menu based on a given name
     * @param name Name of the menu to give
     * @return Menu*
     */
    Menu* GetCurrentMenu() const;

    static constexpr auto reflect_members() {
        return std::make_tuple(
            Field<Window, int>{"flags", &Window::flags},
            Field<Window, int>{"is_open", &Window::is_open},
            Field<Window, SDL_Window*>{"window", &Window::window},
            Field<Window, SDL_Renderer*>{"renderer", &Window::renderer},
            Field<Window, std::unordered_map<std::string, Menu*>>{"menus", &Window::menus},
            Field<Window, Menu*>{"current_menu", &Window::current_menu},
            Field<Window, std::unordered_map<std::string, SDL_Cursor*>>{"Cursors", &Window::Cursors},
            Field<Window, std::string>{"current_cursor_name", &Window::current_cursor_name},
            Field<Window, int>{"width", &Window::width},
            Field<Window, int>{"height", &Window::height}
        );
    }

};


#endif //HERION_HERO_WINDOW_HPP
