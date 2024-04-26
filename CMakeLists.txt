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
    src/grid/cursor.cpp
    src/game_loop/game_loop.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_XOPEN_SOURCE_EXTENDED")

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(LIBRARIES_TO_LINK ncursesw)
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(LIBRARIES_TO_LINK ncurses)
endif()

add_executable(DungeonGenerator ${SOURCES})
target_link_libraries(DungeonGenerator ${LIBRARIES_TO_LINK})
target_include_directories(DungeonGenerator PRIVATE ${CURSES_INCLUDE_DIRS})
