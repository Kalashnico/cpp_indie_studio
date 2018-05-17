cmake_minimum_required(VERSION 2.6)
PROJECT(PlayerTest)

SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
SET(CMAKE_CXX_FLAGS_DEBUG  "-g")
SET(CMAKE_CXX_FLAGS "-lXxf86vm")
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})


IF(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE RelWithDebInfo)
ENDIF(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)

FIND_PACKAGE(X11)
FIND_PACKAGE(OpenGL)
INCLUDE_DIRECTORIES(
        ${PROJECT_SOURCE_DIR}/include
        ${OPENGL_SOURCE_DIR}/include
        ${X11_SOURCE_DIR}/include
        src/Map
        src/Boxes
        src/Loot
        src/Player_IA
)

FILE(GLOB SRCS src/*.cpp)
FILE(GLOB HDRS src/*.hpp)

ADD_EXECUTABLE(IrrlichtTests
        ${SRCS}
        ${HDRS}
        src/main.cpp src/Player_IA/IA.cpp src/Player_IA/IA.hpp src/Player_IA/Player.cpp src/Player_IA/Player.hpp)

TARGET_LINK_LIBRARIES(IrrlichtTests
        ${PROJECT_SOURCE_DIR}/lib/libIrrlicht.a
        ${OPENGL_LIBRARIES}
        ${X11_LIBRARIES}
)