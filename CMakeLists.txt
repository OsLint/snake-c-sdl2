cmake_minimum_required(VERSION 3.25)
project(SnakeC C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_INSTALL_RPATH "@loader_path")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

find_package(SDL2 REQUIRED COMPONENTS SDL2)


add_executable(SnakeC main.c game.c game.h player.c player.h)


target_link_libraries(SnakeC PRIVATE SDL2::SDL2)

find_library(SDL2_LIBRARY NAMES SDL2 PATHS /path/to/SDL2.framework/Libraries)

if (SDL2_LIBRARY)
    target_link_libraries(SnakeC PRIVATE ${SDL2_LIBRARY})
else()
    message(FATAL_ERROR "SDL2 library not found")
endif()
