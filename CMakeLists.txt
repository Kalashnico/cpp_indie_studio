cmake_minimum_required(VERSION 3.9)
project(cpp_indie_studio)

set(CMAKE_CXX_STANDARD 11)

include_directories(src/Boxes
                    src/Loot)

add_executable(cpp_indie_studio
            src/main.cpp src/Boxes/Box.cpp src/Boxes/Box.hpp src/Loot/Loot.cpp src/Loot/Loot.hpp)
