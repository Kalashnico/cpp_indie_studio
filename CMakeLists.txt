cmake_minimum_required(VERSION 3.9)
project(cpp_indie_studio)

set(CMAKE_CXX_STANDARD 11)

add_executable(cpp_indie_studio
        src/Sound/SoundManager.cpp
        src/Sound/SoundManager.hpp
        src/main.cpp)
