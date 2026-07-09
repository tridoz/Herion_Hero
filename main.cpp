#include "src/Entities/hpp/Player.hpp"
#include "src/Textures/hpp/TextureManager.hpp"
#include "src/UI/hpp/Menu.hpp"
#include "src/UI/hpp/Window.hpp"
#include "src/Utils/hpp/ButtonsFunctions.hpp"
#include "src/Utils/hpp/InputProcessor.hpp"
#include "src/Utils/hpp/Logger.hpp"
#include "src/Utils/hpp/STRINGS.hpp"
#include "src/WorldBuilding/hpp/RoomManager.hpp"

#include <cstdlib>
#include <fstream>
#include <string>
#include <unistd.h>

#include "src/Exceptions/hpp/HerionFileException.hpp"
#include "src/Sound/hpp/SoundBoard.hpp"
#include "src/UI/hpp/ButtonMenu.hpp"
#include "src/UI/hpp/ScrollPaneMenu.hpp"
#include "src/WorldBuilding/hpp/EditorRoom.hpp"

#ifdef _WIN32
#include <stdlib.h>
#endif

int LoadEnv() {

  std::string base_path = "../";
  std::string path = ".env";

  std::ifstream file;

  try {
    FileOpener::OpenFileInput(file, base_path + path);
  } catch (HerionException::File::FileException &ex) {
    ex.UpdateStackTrace(GET_CONTEXT());
    throw;
  }

  if (!file.is_open()) {
    Logger::LogErr(std::time(nullptr), "LOADING", "Main", "LoadEnv",
                   " file: [" + path + "] " + strerror(errno));
    return 0;
  }

  // Logger::LogOk(
  //     std::time(nullptr),
  //     "LOADING",
  //     "Main",
  //     "LoadEnv",
  //     ".env file loaded correctly"
  //     );

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty() || line[0] == '#')
      continue;

    size_t eqPos = line.find('=');

    if (eqPos == std::string::npos)
      continue;

    std::string key = line.substr(0, eqPos);
    std::string value = line.substr(eqPos + 1);

    key.erase(0, key.find_first_not_of(" \t"));
    key.erase(key.find_last_not_of(" \t") + 1);
    value.erase(0, value.find_first_not_of(" \t"));
    value.erase(value.find_last_not_of(" \t") + 1);
#ifdef _WIN32
    _putenv_s(key.c_str(), value.c_str());
#else
    setenv(key.c_str(), value.c_str(), 1);
#endif
  }

  file.close();
  return 1;
}

int main(int argc, char *argv[]) {

  // LoadEnv();
  // find src_game \( -name "*.cpp" -o -name "*.hpp" \) -exec wc -l {} + | sort
  // -n

  SoundBoard::Init();
  SoundBoard::LoadSound("prova", "../sounds/prova.mp3");

  Logger::EnableSTDOUTLogging();

  Window *window;

  try {
    window = new Window("Herion Hero");
  } catch (HerionException::File::FileException &ex) {
    ex.UpdateStackTrace(GET_CONTEXT());
    Logger::LogStackTrace(std::time(nullptr), ex.GetStackTrace());
    return -1;
  }

  std::unordered_map<std::string, Window *> editors_windows = {
      {"TEXTURE_SELECTION", new Window("Texture selection", 500, 300)},
      {"ACTION_SELECTION", new Window("Action selection", 500, 300)},
      {"ENTITY_SELECTION", new Window("Entity selection", 500, 300)}};

  InputProcessor processor;

  TextureManager main_texture_manager;
  TextureManager texture_selection_texture_manager;
  TextureManager action_selection_texture_manager;
  TextureManager entity_selection_texture_manager;

  RoomManager game_room_manager;

  EditorRoom editor_room;

  Player player;

  ButtonMenu main_menu;
  ButtonMenu general_settings_menu;
  ButtonMenu graphics_settings_menu;
  ButtonMenu audio_settings_menu;

  ButtonMenu pause_menu;
  ButtonMenu editor_menu;

  ButtonMenu action_selection_menu;

  ScrollPaneMenu texture_selection_menu;
  ScrollPaneMenu entity_selection_menu;

  Player::PlayerState player_state;
  Player::GameMode game_mode;

  ButtonsFunctions::SetPlayer(&player);

  std::vector<struct JSONParser::entities::EntityProperties> prop =
      JSONParser::entities::GetEntityProperties("maps/room1/entities.json");

  window->SetMenu(Strings::Menus::Main_Window::Names::main_menu_name,
                  &main_menu);

  window->SetMenu(
      Strings::Menus::Main_Window::Names::general_settings_menu_name,
      &general_settings_menu);
  window->SetMenu(Strings::Menus::Main_Window::Names::pause_menu_name,
                  &pause_menu);
  window->SetMenu(Strings::Menus::Main_Window::Names::editor_menu_name,
                  &editor_menu);

  window->SetMenu(
      Strings::Menus::Main_Window::Names::graphics_settings_menu_name,
      &graphics_settings_menu);
  window->SetMenu(Strings::Menus::Main_Window::Names::audio_settings_menu_name,
                  &audio_settings_menu);

  editors_windows.at("TEXTURE_SELECTION")
      ->SetMenu("TEXTURE_SELECTION", &texture_selection_menu);
  editors_windows.at("TEXTURE_SELECTION")->SetCurrentMenu("TEXTURE_SELECTION");

  editors_windows.at("ACTION_SELECTION")
      ->SetMenu("ACTION_SELECTION", &action_selection_menu);
  editors_windows.at("ACTION_SELECTION")->SetCurrentMenu("ACTION_SELECTION");

  editors_windows.at("ENTITY_SELECTION")
      ->SetMenu("ENTITY_SELECTION", &entity_selection_menu);
  editors_windows.at("ENTITY_SELECTION")->SetCurrentMenu("ENTITY_SELECTION");

  // window.LoadCursors( Strings::Textures::Cursors::all_cursors_path );

  main_texture_manager.SetRenderer(window->GetRenderer());
  texture_selection_texture_manager.SetRenderer(
      editors_windows.at("TEXTURE_SELECTION")->GetRenderer());
  action_selection_texture_manager.SetRenderer(
      editors_windows.at("ACTION_SELECTION")->GetRenderer());
  entity_selection_texture_manager.SetRenderer(
      editors_windows.at("ENTITY_SELECTION")->GetRenderer());
  try {

    main_texture_manager.LoadTextures(
        Strings::Textures::Paths::all_textures_path);
    texture_selection_texture_manager.LoadTextures(
        Strings::Textures::Paths::all_textures_path);
    action_selection_texture_manager.LoadTextures(
        Strings::Textures::Paths::all_textures_path);
    entity_selection_texture_manager.LoadTextures(
        Strings::Textures::Paths::all_textures_path);

  } catch (HerionException::File::FileException &ex) {
    ex.UpdateStackTrace(GET_CONTEXT());
    Logger::LogStackTrace(std::time(nullptr), ex.GetStackTrace());
    return -1;
  }

  game_room_manager.SetTextureManager(&main_texture_manager);
  game_room_manager.SetDimensions(window->GetWidth(), window->GetHeight(), 32,
                                  18);

  try {
    game_room_manager.GenerateRoom(RoomManager::DIRECTION::DIR_NONE,
                                   "maps/room1/");
  } catch (HerionException::File::FileException &ex) {
    ex.UpdateStackTrace(GET_CONTEXT());
    Logger::LogStackTrace(std::time(nullptr), ex.GetStackTrace());
    return -1;
  }

  main_menu.SetTextureManager(&main_texture_manager);
  main_menu.SetDimension(static_cast<float>(window->GetWidth()),
                         static_cast<float>(window->GetHeight()));

  general_settings_menu.SetTextureManager(&main_texture_manager);
  general_settings_menu.SetDimension(static_cast<float>(window->GetWidth()),
                                     static_cast<float>(window->GetHeight()));

  graphics_settings_menu.SetTextureManager(&main_texture_manager);
  graphics_settings_menu.SetDimension(static_cast<float>(window->GetWidth()),
                                      static_cast<float>(window->GetHeight()));

  audio_settings_menu.SetTextureManager(&main_texture_manager);
  audio_settings_menu.SetDimension(static_cast<float>(window->GetWidth()),
                                   static_cast<float>(window->GetHeight()));

  pause_menu.SetTextureManager(&main_texture_manager);
  pause_menu.SetDimension(static_cast<float>(window->GetWidth()),
                          static_cast<float>(window->GetHeight()));

  editor_menu.SetTextureManager(&main_texture_manager);
  editor_menu.SetDimension(static_cast<float>(window->GetWidth()),
                           static_cast<float>(window->GetHeight()));

  texture_selection_menu.SetTextureManager(&texture_selection_texture_manager);
  texture_selection_menu.SetDimension(
      static_cast<float>(editors_windows.at("TEXTURE_SELECTION")->GetWidth()),
      static_cast<float>(editors_windows.at("TEXTURE_SELECTION")->GetHeight()));

  action_selection_menu.SetTextureManager(&action_selection_texture_manager);
  action_selection_menu.SetDimension(
      static_cast<float>(editors_windows.at("ACTION_SELECTION")->GetWidth()),
      static_cast<float>(editors_windows.at("ACTION_SELECTION")->GetHeight()));

  entity_selection_menu.SetTextureManager(&entity_selection_texture_manager);
  action_selection_menu.SetDimension(
      static_cast<float>(editors_windows.at("ENTITY_SELECTION")->GetWidth()),
      static_cast<float>(editors_windows.at("ENTITY_SELECTION")->GetHeight()));

  try {

    main_menu.LoadConfiguration(
        Strings::Menus::Main_Window::Paths::main_menu_config_path);

    general_settings_menu.LoadConfiguration(
        Strings::Menus::Main_Window::Paths::general_settings_menu_config_path);
    graphics_settings_menu.LoadConfiguration(
        Strings::Menus::Main_Window::Paths::graphics_settings_menu_config_path);
    audio_settings_menu.LoadConfiguration(
        Strings::Menus::Main_Window::Paths::audio_settings_menu_config_path);

    pause_menu.LoadConfiguration(
        Strings::Menus::Main_Window::Paths::pause_menu_config_path);
    editor_menu.LoadConfiguration(
        Strings::Menus::Main_Window::Paths::editor_menu_config_path);

    texture_selection_menu.LoadConfiguration(
        Strings::Menus::Level_Editors_Window::Paths::
            texture_selection_menu_config_path);
    action_selection_menu.LoadConfiguration(
        Strings::Menus::Level_Editors_Window::Paths::
            action_selection_menu_config_path);
    entity_selection_menu.LoadConfiguration(
        Strings::Menus::Level_Editors_Window::Paths::
            entity_selection_menu_config_path);

  } catch (HerionException::File::FileException &ex) {
    ex.UpdateStackTrace(GET_CONTEXT());
    Logger::LogStackTrace(std::time(nullptr), ex.GetStackTrace());
    return -1;
  }

  processor.SetMenus(Strings::Menus::Main_Window::Names::main_menu_name,
                     &main_menu);
  processor.SetMenus(
      Strings::Menus::Main_Window::Names::general_settings_menu_name,
      &general_settings_menu);
  processor.SetMenus(
      Strings::Menus::Main_Window::Names::graphics_settings_menu_name,
      &graphics_settings_menu);
  processor.SetMenus(
      Strings::Menus::Main_Window::Names::audio_settings_menu_name,
      &audio_settings_menu);
  processor.SetMenus(Strings::Menus::Main_Window::Names::pause_menu_name,
                     &pause_menu);
  processor.SetMenus(Strings::Menus::Main_Window::Names::editor_menu_name,
                     &editor_menu);
  processor.SetMenus(
      Strings::Menus::Level_Editors_Window::Names::texture_selection_menu_name,
      &texture_selection_menu);
  processor.SetMenus(
      Strings::Menus::Level_Editors_Window::Names::action_selection_menu_name,
      &action_selection_menu);
  processor.SetMenus(
      Strings::Menus::Level_Editors_Window::Names::entity_selection_menu_name,
      &entity_selection_menu);

  processor.SetTextureManager(
      Strings::TextureManagers::Names::main_texture_manager_name,
      &main_texture_manager);
  processor.SetTextureManager(
      Strings::TextureManagers::Names::texture_selection_menu_name,
      &texture_selection_texture_manager);
  processor.SetTextureManager(
      Strings::TextureManagers::Names::action_selection_menu_name,
      &action_selection_texture_manager);
  processor.SetTextureManager(
      Strings::TextureManagers::Names::entity_seleciton_menu_name,
      &entity_selection_texture_manager);

  processor.SetEditorRoom(&editor_room);

  processor.SetWindowTools(editors_windows);

  processor.SetPlayer(&player);
  processor.SetRoomManager(&game_room_manager);

  player.SetTextureManager(&main_texture_manager);

  SDL_Event event;

  Uint32 last_frame_time = SDL_GetTicks();

  game_room_manager.GenerateEditorRoom(&editor_room, "maps/room1/");

  player.ParseEntityProperties(prop[0]);

  while (!processor.ShouldQuit() &&
         player.GetGameMode() != Player::GameMode::EXIT) {

    Uint32 current_time = SDL_GetTicks();
    float deltaTime = (current_time - last_frame_time) / 1000.0f;
    last_frame_time = current_time;

    // 🔥 FIX IMPORTANTE: evita valori instabili
    deltaTime = std::clamp(deltaTime, 0.0f, 0.033f);

    while (SDL_PollEvent(&event)) {
      processor.SetEvent(event);
      try {
        processor.Process();
      } catch (HerionException::File::FileException &e) {
        e.UpdateStackTrace(GET_CONTEXT());
        Logger::LogStackTrace(std::time(nullptr), e.GetStackTrace());
        return 0;
      }
    }

    if (JSONParser::graphics::Changed()) {

      window->Resize();

      main_menu.SetDimension(static_cast<float>(window->GetWidth()),
                             static_cast<float>(window->GetHeight()));
      general_settings_menu.SetDimension(
          static_cast<float>(window->GetWidth()),
          static_cast<float>(window->GetHeight()));
      graphics_settings_menu.SetDimension(
          static_cast<float>(window->GetWidth()),
          static_cast<float>(window->GetHeight()));
      audio_settings_menu.SetDimension(static_cast<float>(window->GetWidth()),
                                       static_cast<float>(window->GetHeight()));
      pause_menu.SetDimension(static_cast<float>(window->GetWidth()),
                              static_cast<float>(window->GetHeight()));
      editor_menu.SetDimension(static_cast<float>(window->GetWidth()),
                               static_cast<float>(window->GetHeight()));

      try {
        main_menu.LoadConfiguration(
            Strings::Menus::Main_Window::Paths::main_menu_config_path);

        general_settings_menu.LoadConfiguration(
            Strings::Menus::Main_Window::Paths::
                general_settings_menu_config_path);
        graphics_settings_menu.LoadConfiguration(
            Strings::Menus::Main_Window::Paths::
                graphics_settings_menu_config_path);
        audio_settings_menu.LoadConfiguration(
            Strings::Menus::Main_Window::Paths::
                audio_settings_menu_config_path);

        pause_menu.LoadConfiguration(
            Strings::Menus::Main_Window::Paths::pause_menu_config_path);
        editor_menu.LoadConfiguration(
            Strings::Menus::Main_Window::Paths::editor_menu_config_path);

        texture_selection_menu.LoadConfiguration(
            Strings::Menus::Level_Editors_Window::Paths::
                texture_selection_menu_config_path);
        action_selection_menu.LoadConfiguration(
            Strings::Menus::Level_Editors_Window::Paths::
                action_selection_menu_config_path);
        entity_selection_menu.LoadConfiguration(
            Strings::Menus::Level_Editors_Window::Paths::
                entity_selection_menu_config_path);

      } catch (HerionException::File::FileException &ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        Logger::LogStackTrace(std::time(nullptr), ex.GetStackTrace());
        return -1;
      }

      game_room_manager.ResizeRoom();
      game_room_manager.ResizeEditorRoom(&editor_room);

      player.Resize();
    }

    if (JSONParser::audio::Changed()) {

      JSONParser::audio::ChangesApplied();

      try {
        audio_settings_menu.LoadConfiguration(
            Strings::Menus::Main_Window::Paths::
                audio_settings_menu_config_path);
      } catch (HerionException::File::FileException &ex) {
        ex.UpdateStackTrace(GET_CONTEXT());
        Logger::LogStackTrace(std::time(nullptr), ex.GetStackTrace());
        return -1;
      }
    }

    window->SetColor(COLORS::BLACK);
    window->Clear();

    game_mode = player.GetGameMode();

    switch (game_mode) {

    default:
      break;

    case Player::GameMode::MAIN_MENU:
      window->SetCurrentMenu(
          Strings::Menus::Main_Window::Names::main_menu_name);
      window->GetCurrentMenu()->Draw(window->GetRenderer());
      break;

    case Player::GameMode::GENERAL_SETTINGS_MENU:
      window->SetCurrentMenu(
          Strings::Menus::Main_Window::Names::general_settings_menu_name);
      window->GetCurrentMenu()->Draw(window->GetRenderer());
      break;

    case Player::GameMode::GRAPHICS_SETTINGS_MENU:
      window->SetCurrentMenu(
          Strings::Menus::Main_Window::Names::graphics_settings_menu_name);
      window->GetCurrentMenu()->Draw(window->GetRenderer());
      break;

    case Player::GameMode::AUDIO_SETTINGS_MENU:
      window->SetCurrentMenu(
          Strings::Menus::Main_Window::Names::audio_settings_menu_name);
      window->GetCurrentMenu()->Draw(window->GetRenderer());
      break;

    case Player::GameMode::PAUSE_MENU:
      window->SetCurrentMenu(
          Strings::Menus::Main_Window::Names::pause_menu_name);
      window->GetCurrentMenu()->Draw(window->GetRenderer());
      break;

    case Player::GameMode::EDITOR_MENU:
      window->SetCurrentMenu(
          Strings::Menus::Main_Window::Names::editor_menu_name);
      window->GetCurrentMenu()->Draw(window->GetRenderer());
      break;

    case Player::GameMode::LEVEL_EDITOR:
      editor_room.Draw(window->GetRenderer());

      if (editor_room.ShouldDrawAxis())
        editor_room.DrawAxis(window->GetRenderer());

      if (editor_room.ShouldDrawHitboxes())
        editor_room.DrawHitboxes(window->GetRenderer());

      for (const auto &[editor_win_name, editor_win] : editors_windows) {
        if (editor_win->IsOpen()) {
          editor_win->SetColor(COLORS::BLACK);
          editor_win->Clear();
          editor_win->GetCurrentMenu()->Draw(editor_win->GetRenderer());
          editor_win->Present();
          editor_win->Sleep();
        }
      }
      break;

    case Player::GameMode::IN_GAME:
      game_room_manager.DrawCurrentRoom(window->GetRenderer());

      processor.update_player_movement(deltaTime);
      player.Update(deltaTime);
      player.Draw(window->GetRenderer());
      break;
    }

    window->Present();
    window->Sleep();
  }
}
