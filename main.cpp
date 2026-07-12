#include "src/Engine/hpp/Engine.hpp"

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
    Logger::LogErr(
      std::time(nullptr), "LOADING", "Main", "LoadEnv",
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

  Engine* e = new Engine();

  try {
      e->Init();
  } catch( HerionException::File::FileException& ex ) {
      ex.UpdateStackTrace( GET_CONTEXT() );
      Logger::LogStackTrace(
          std::time(nullptr),
          ex.GetStackTrace()
      );
      return -1;
  }



  try {
      e->Run();
  } catch (HerionException::File::FileException& ex ) {
      ex.UpdateStackTrace( GET_CONTEXT() );
      Logger::LogStackTrace(
          std::time(nullptr),
          ex.GetStackTrace()
      );
      return -1;
  }


}
