cmake_minimum_required(VERSION 3.20)
project(Herion_Hero)

set(CMAKE_CXX_STANDARD 20)

# SDL3
set(SDL3_DIR "${CMAKE_SOURCE_DIR}/SDL3")
include_directories("${SDL3_DIR}/include")
set(SDL3_LIB "${SDL3_DIR}/lib/SDL3.lib")

# SDL_image
set(SDL_IMAGE_DIR "${CMAKE_SOURCE_DIR}/SDL3")
include_directories("${SDL_IMAGE_DIR}/include")
set(SDL_IMAGE_LIB "${SDL_IMAGE_DIR}/lib/SDL3_image.lib")

# SDL_ttf
set(SDL_TTF_DIR "${CMAKE_SOURCE_DIR}/SDL3")
include_directories("${SDL_TTF_DIR}/include")
set(SDL_TTF_LIB "${SDL_TTF_DIR}/lib/SDL3_ttf.lib")

# Executable
add_executable(Herion_Hero main.cpp
        src/TextureManager.hpp
        src/InputProcessor.cpp
        src/Logger.cpp
        src/Window.cpp
        src/TextureManager.cpp
        src/Texture.cpp
        src/Texture.hpp
        src/Tile.cpp
        src/Tile.hpp
        src/Room.cpp
        src/Room.hpp
        src/RoomManager.cpp
        src/RoomManager.hpp
)

# Link libraries
target_link_libraries(Herion_Hero PRIVATE
        ${SDL3_LIB}
        ${SDL_IMAGE_LIB}
        ${SDL_TTF_LIB}
)

add_custom_command(TARGET Herion_Hero POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL3_DIR}/SDL3.dll" "$<TARGET_FILE_DIR:Herion_Hero>"
)
add_custom_command(TARGET Herion_Hero POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL_IMAGE_DIR}/SDL3_image.dll" "$<TARGET_FILE_DIR:Herion_Hero>"
)
add_custom_command(TARGET Herion_Hero POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL_TTF_DIR}/SDL3_ttf.dll" "$<TARGET_FILE_DIR:Herion_Hero>"
)
