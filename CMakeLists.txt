cmake_minimum_required(VERSION 3.16)
project(tetris_sdl2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(tetris
  src/main.cpp
  src/game.cpp
  src/board.cpp
  src/pieces.cpp
  src/renderer.cpp
)

# Find SDL2 using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

target_include_directories(tetris PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_directories(tetris PRIVATE ${SDL2_LIBRARY_DIRS})
target_link_libraries(tetris PRIVATE ${SDL2_LIBRARIES})
target_compile_options(tetris PRIVATE ${SDL2_CFLAGS_OTHER})

if (APPLE)
  target_compile_definitions(tetris PRIVATE SDL_MAIN_HANDLED)
endif()
