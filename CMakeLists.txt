cmake_minimum_required(VERSION 3.20)

project(Herion_Hero)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g -O0)
endif()

set(SDL3_DIR "${CMAKE_SOURCE_DIR}/SDL3")

include_directories(
        "${SDL3_DIR}/include"

        "${CMAKE_SOURCE_DIR}/src_game/Utils/hpp"
        "${CMAKE_SOURCE_DIR}/src_game/Entities/hpp"
        "${CMAKE_SOURCE_DIR}/src_game/Textures/hpp"
        "${CMAKE_SOURCE_DIR}/src_game/UI/hpp"
        "${CMAKE_SOURCE_DIR}/src_game/WorldBuilding/hpp"
        "${CMAKE_SOURCE_DIR}/src_game/Sound/hpp"
        "${CMAKE_SOURCE_DIR}/src_game/Exceptions/hpp"
)

file(GLOB_RECURSE SRC_FILES
        "${CMAKE_SOURCE_DIR}/src_game/*.cpp"
        "${CMAKE_SOURCE_DIR}/main.cpp"
)

add_executable(Herion_Hero ${SRC_FILES})

if (MSVC)
    target_compile_options(Herion_Hero PRIVATE /w)
else()
    target_compile_options(Herion_Hero PRIVATE -w)
endif()

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
