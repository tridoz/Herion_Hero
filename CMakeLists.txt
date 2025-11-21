cmake_minimum_required(VERSION 3.20)
project(Herion_Hero)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(SDL3_DIR "${CMAKE_SOURCE_DIR}/SDL3")

include_directories("${SDL3_DIR}/include")
include_directories("${CMAKE_SOURCE_DIR}/BOOST/boost_1_89_0")

file(GLOB SRC_FILES
        ${CMAKE_SOURCE_DIR}/src_game/*.cpp
        ${CMAKE_SOURCE_DIR}/src_game/*.hpp
        ${CMAKE_SOURCE_DIR}/main.cpp
)


add_executable(Herion_Hero ${SRC_FILES}
        src_game/COLORS.cpp
        src_game/COLORS.hpp
        src_game/Player.cpp
        src_game/Player.hpp
        src_game/Menu.cpp
        src_game/Menu.hpp
        src_game/Button.cpp
        src_game/Button.hpp
        src_game/ButtonsFunctions.cpp
        src_game/ButtonsFunctions.hpp)

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
    )
endif()
