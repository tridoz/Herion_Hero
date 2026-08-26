#include "../../Editor/hpp/ImageEditor.hpp"
#include "../../Entities/hpp/Player.hpp"
#include "../../Exceptions/hpp/HerionFileException.hpp"
#include "../../Sound/hpp/SoundBoard.hpp"
#include "../../Textures/hpp/TextureManager.hpp"
#include "../../UI/hpp/ButtonMenu.hpp"
#include "../../UI/hpp/Menu.hpp"
#include "../../UI/hpp/ScrollPaneMenu.hpp"
#include "../../UI/hpp/Window.hpp"
#include "../../Utils/hpp/ButtonsFunctions.hpp"
#include "../../Utils/hpp/InputProcessor.hpp"
#include "../../Utils/hpp/Logger.hpp"
#include "../../Utils/hpp/STRINGS.hpp"
#include "../../WorldBuilding/hpp/EditorRoom.hpp"
#include "../../WorldBuilding/hpp/RoomManager.hpp"

class Engine {

  private:
    float deltaTime;

    Window* main_window;
    std::unordered_map<std::string, Window*> editors_windows;

    InputProcessor* processor;
    TextureManager* main_texture_manager;
    TextureManager* texture_selection_texture_manager;
    TextureManager* action_selection_texture_manager;
    TextureManager* entity_selection_texture_manager;
    RoomManager* game_room_manager;
    EditorRoom* editor_room;
    ImageEditor* img_editor;
    Player* player;

    ButtonMenu* main_menu;
    ButtonMenu* general_settings_menu;
    ButtonMenu* graphics_settings_menu;
    ButtonMenu* audio_settings_menu;
    ButtonMenu* pause_menu;
    ButtonMenu* editor_menu;
    ButtonMenu* action_selection_menu;

    ScrollPaneMenu* texture_selection_menu;
    ScrollPaneMenu* entity_selection_menu;

    void LoadMenusConfigurations();
    void SetMenusDimensions();

    void LoadTextureManagers();

    void InitWindows();
    void InitTextureManagers();
    void InitRoomManager();
    void InitMenus();
    void InitInputProcessor();
    void InitPlayer();

    void CheckGameMode();

  public:
    Engine();
    ~Engine();

    enum class GameState : std::uint8_t {
        MAIN_MENU,
        GENERAL_SETTINGS_MENU,
        GRAPHICS_SETTINGS_MENU,
        AUDIO_SETTINGS_MENU,
        PAUSE_MENU,
        EDITOR_MENU,
        LEVEL_EDITOR,
        ANIMATION_EDITOR,
        IN_GAME,
        EXIT
    };
    static GameState state;
    static GameState previous_state;

    static void SetGameState(GameState new_state);
    static GameState GetGameState();
    static GameState GetPreviousState();

    void Init();

    void Run();
};
