cmake_minimum_required(VERSION 3.16)
project(StoneKnights VERSION 1.0.0 LANGUAGES CXX)

# Specify C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find SDL2 packages using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
pkg_check_modules(SDL2_GFX REQUIRED SDL2_gfx)

# Include directories
include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${SDL2_GFX_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Source files
set(SOURCES
    main.cpp
    Game.cpp
    Board.cpp
    Piece.cpp
    Knight.cpp
    Stone.cpp
    Player.cpp
    TextureManager.cpp
    InputHandler.cpp
    GameState.cpp
    Position.cpp
    UI.cpp
)

# Header files
set(HEADERS
    Game.h
    Board.h
    Piece.h
    Knight.h
    Stone.h
    Player.h
    TextureManager.h
    InputHandler.h
    GameState.h
    Position.h
    UI.h
    Constants.h
)

# Add executable
add_executable(StoneKnights ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(StoneKnights
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_GFX_LIBRARIES}
)

# Create assets directory and copy assets
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/assets)
file(GLOB ASSETS "assets/*")
foreach(ASSET ${ASSETS})
    file(COPY ${ASSET} DESTINATION ${CMAKE_BINARY_DIR}/bin/assets)
endforeach()

# Compiler warnings
if(MSVC)
    target_compile_options(StoneKnights PRIVATE /W4)
else()
    target_compile_options(StoneKnights PRIVATE -Wall -Wextra -Wpedantic)
endif()
