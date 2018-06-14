cmake_minimum_required(VERSION 2.6)
PROJECT(bomberman)

SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
SET(CMAKE_CXX_FLAGS_DEBUG  "-g")
SET(CMAKE_CXX_FLAGS "-lXxf86vm -lpthread -lsfml-audio")
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
SET(RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/..)

IF(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE RelWithDebInfo)
ENDIF(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)

FIND_PACKAGE(X11)
FIND_PACKAGE(OpenGL)
INCLUDE_DIRECTORIES(
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/src/Graphic
	${OPENGL_SOURCE_DIR}/include
	${X11_SOURCE_DIR}/include
	src/Player_AI
	src/Object
	src/Object/Boxes
	src/Object/Wall
	src/Object/Fire
	src/Object/Bomb
	src/Core
	src/Map
	src/Graphic
	src/Sound
)

FILE(GLOB SRCS src/*.cpp)

FILE(GLOB HDRS_IRR include/*.h)

FILE(GLOB SRCS_GRAPHICS src/Graphic/*.cpp)
FILE(GLOB HDRS_CORE src/Core/*.hpp)
FILE(GLOB SRCS_MAP src/Map/*.cpp)
FILE(GLOB SRCS_PLAYER src/Player_AI/*.cpp)
FILE(GLOB HDRS_GRAPHICS src/Graphic/*.hpp)
FILE(GLOB SRCS_SOUND src/Sound/*.cpp)
FILE(GLOB HDRS_SOUND src/Sound/*.hpp)
FILE(GLOB SRCS_OBJECTS src/Core/*.cpp src/Object/*.cpp src/Object/Bomb/*.cpp src/Object/Boxes/*.cpp src/Object/Fire/*.cpp src/Object/Wall/*.cpp)

ADD_EXECUTABLE(bomberman
        ${SRCS}
        ${HDRS_IRR}
        ${SRCS_GRAPHICS}
        ${SRCS_MAP}
        ${SRCS_PLAYER}
        ${SRCS_OBJECTS}
	${HDRS_CUSTOM}
	${SRCS_SOUND}
	${HDRS_SOUND}
)

TARGET_LINK_LIBRARIES(bomberman
        ${PROJECT_SOURCE_DIR}/lib/libIrrlicht.a
        ${OPENGL_LIBRARIES}
        ${X11_LIBRARIES}
)
