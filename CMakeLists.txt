cmake_minimum_required(VERSION 3.16)
project(tetris_sdl2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tetris
  src/main.cpp
  src/game.cpp
  src/board.cpp
  src/pieces.cpp
  src/renderer.cpp
)

find_package(SDL2 REQUIRED)

if (TARGET SDL2::SDL2)
  target_link_libraries(tetris PRIVATE SDL2::SDL2)
else()
  target_include_directories(tetris PRIVATE ${SDL2_INCLUDE_DIRS})
  target_link_libraries(tetris PRIVATE ${SDL2_LIBRARIES})
endif()

if (APPLE)
  target_compile_definitions(tetris PRIVATE SDL_MAIN_HANDLED)
endif()
