cmake_minimum_required(VERSION 3.9)
project(cpp_indie_studio)

set(CMAKE_CXX_STANDARD 11)

include_directories(src/ src/Object/Boxes src/Loot src/Object/Bomb src/Object/Wall)

add_executable(cpp_indie_studio
        src/Object/Bomb/Bomb.cpp
        src/Object/Boxes/Box.cpp
        src/Object/Boxes/Loot.cpp
        src/Object/Wall/Wall.cpp
        src/Object/AObject.cpp
        src/main.cpp)
