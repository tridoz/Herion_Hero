cmake_minimum_required(VERSION 3.20)
project(Herion_Hero)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Percorso unificato SDL3
set(SDL3_DIR "${CMAKE_SOURCE_DIR}/SDL3")

# Include unificato per SDL3, SDL3_image e SDL3_ttf
include_directories("${SDL3_DIR}/include")

# Sorgenti del progetto
file(GLOB SRC_FILES
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/src/*.hpp
        ${CMAKE_SOURCE_DIR}/main.cpp
)

add_executable(Herion_Hero ${SRC_FILES})

# Link delle librerie in base alla piattaforma
if(WIN32)
    target_link_libraries(Herion_Hero PRIVATE
            "${SDL3_DIR}/lib/Windows/SDL3.lib"
            "${SDL3_DIR}/lib/Windows/SDL3_image.lib"
            "${SDL3_DIR}/lib/Windows/SDL3_ttf.lib"
    )

    # Copia le DLL accanto all'eseguibile
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
