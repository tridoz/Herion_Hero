cmake_minimum_required(VERSION 3.20)
project(Herion_Hero)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(SDL3_DIR "${CMAKE_SOURCE_DIR}/SDL3")

include_directories("${SDL3_DIR}/include")

file(GLOB SRC_FILES
        ${CMAKE_SOURCE_DIR}/src_game/Utils/cpp/*.cpp
        ${CMAKE_SOURCE_DIR}/src_game/Utils/hpp/*.hpp

        ${CMAKE_SOURCE_DIR}/src_game/Entities/cpp/*.cpp
        ${CMAKE_SOURCE_DIR}/src_game/Entities/hpp/*.hpp

        ${CMAKE_SOURCE_DIR}/src_game/Textures/cpp/*.cpp
        ${CMAKE_SOURCE_DIR}/src_game/Textures/hpp/*.hpp

        ${CMAKE_SOURCE_DIR}/src_game/UI/cpp/*.cpp
        ${CMAKE_SOURCE_DIR}/src_game/UI/hpp/*.hpp

        ${CMAKE_SOURCE_DIR}/src_game/WorldBuilding/cpp/*.cpp
        ${CMAKE_SOURCE_DIR}/src_game/WorldBuilding/hpp/*.hpp

        ${CMAKE_SOURCE_DIR}/src_TCP/cpp/*.cpp
        ${CMAKE_SOURCE_DIR}/src_TCP/hpp/*.hpp

        ${CMAKE_SOURCE_DIR}/main.cpp
)


add_executable(Herion_Hero ${SRC_FILES}
        src_game/Utils/cpp/COLORS.cpp
        src_game/Utils/hpp/COLORS.hpp
        src_game/Entities/cpp/Player.cpp
        src_game/Entities/hpp/Player.hpp
        src_game/UI/cpp/Menu.cpp
        src_game/UI/hpp/Menu.hpp
        src_game/UI/cpp/Button.cpp
        src_game/UI/hpp/Button.hpp
        src_game/Utils/cpp/ButtonsFunctions.cpp
        src_game/Utils/hpp/ButtonsFunctions.hpp
        src_game/Utils/hpp/JSONParser.hpp
        src_game/Utils/cpp/Animation.cpp
        src_game/Utils/hpp/Animation.hpp
        src_game/UI/cpp/Text.cpp
        src_game/UI/hpp/Text.hpp
        src_game/Utils/cpp/JSonParserAudio.cpp
        src_game/Utils/cpp/JSONParserGraphics.cpp
        src_game/Utils/cpp/JSONParserMenuConfiguration.cpp
        src_game/Sound/cpp/SoundBoard.cpp
        src_game/Sound/hpp/SoundBoard.hpp
        src_game/Utils/cpp/Save.cpp
        src_game/Utils/hpp/Save.hpp
        src_game/Exceptions/hpp/HerionFileException.hpp
        src_game/Exceptions/cpp/HerionFileException.cpp
        src_game/Utils/cpp/FileOpener.cpp
        src_game/Utils/hpp/FileOpener.hpp
        src_game/Utils/cpp/JSONParserAnimations.cpp
        src_game/Utils/cpp/CMD.cpp
        src_game/Utils/hpp/CMD.hpp
        src_game/WorldBuilding/cpp/EditorRoom.cpp
        src_game/WorldBuilding/hpp/EditorRoom.hpp
        src_game/WorldBuilding/cpp/ForegroundElement.cpp
        src_game/WorldBuilding/hpp/ForegroundElement.hpp
        src_game/WorldBuilding/cpp/BackgroundElement.cpp
        src_game/WorldBuilding/hpp/BackgroundElement.hpp
        src_game/UI/cpp/ButtonMenu.cpp
        src_game/UI/hpp/ButtonMenu.hpp
        src_game/UI/cpp/ScrollPaneMenu.cpp
        src_game/UI/hpp/ScrollPaneMenu.hpp
)

if(WIN32)
    target_link_libraries(Herion_Hero PRIVATE
            "${SDL3_DIR}/lib/Windows/SDL3.lib"
            "${SDL3_DIR}/lib/Windows/SDL3_image.lib"
            "${SDL3_DIR}/lib/Windows/SDL3_ttf.lib"
            ws2_32
    )

    foreach(DLL SDL3 SDL3_image SDL3_ttf)
        add_custom_command(TARGET Herion_Hero POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${SDL3_DIR}/lib/Windows/${DLL}.dll"
                "$<TARGET_FILE_DIR:Herion_Hero>"
        )
    endforeach()

elseif(UNIX)
    target_link_libraries(Herion_Hero PRIVATE
            "${SDL3_DIR}/lib/Linux/libSDL3.so"
            "${SDL3_DIR}/lib/Linux/libSDL3_image.so"
            "${SDL3_DIR}/lib/Linux/libSDL3_ttf.so"
            "${SDL3_DIR}/lib/Linux/libSDL3_mixer.so"
    )
endif()
