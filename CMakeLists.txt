cmake_minimum_required(VERSION 3.9)
project(cpp_indie_studio)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/..)

include_directories(src/Object
		    src/Object/Bomb
		    src/Object/Boxes
		    src/Object/Wall
		    src/Map)

file(GLOB sources main.cpp src/**/*.cpp src/**/**/*.cpp)
set(bomberman ${sources})
add_executable(bomberman ${bomberman})
