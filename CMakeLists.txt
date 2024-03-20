cmake_minimum_required(VERSION 3.10)
project(DungeonGenerator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(SOURCES
    src/main.cpp
    src/heatmap/heatmap.cpp
    src/grid/grid.cpp
    src/grid/terrain.cpp
    src/grid/structure.cpp
    src/grid/unit.cpp
    src/game_loop/game_loop.cpp
)

add_executable(DungeonGenerator ${SOURCES})
target_link_libraries(DungeonGenerator ncursesw)
target_include_directories(DungeonGenerator PRIVATE ${CURSES_INCLUDE_DIRS})
