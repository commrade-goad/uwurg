cmake_minimum_required(VERSION 3.24)

project(uwurg)
set(CMAKE_CXX_STANDARD 23)

include(FetchContent)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(USE_STATIC_LIBS ON CACHE BOOL "" FORCE)
# set(GLFW_BUILD_WAYLAND ON CACHE BOOL "" FORCE)
set(PLATFORM Desktop)

# SET(CMAKE_CXX_FLAGS -ggdb)
add_compile_options(-Wall -Wextra -pedantic)

FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
    URL_HASH ""
)

FetchContent_MakeAvailable(raylib)

set(FILE_IN
    src/TextureManager/TextureManager.cpp
    src/ObjectManager/ObjectManager.cpp
    src/Shaders/ShadersManager.cpp
    src/Window/Window.cpp
    src/Object/Object.cpp
    src/Game/Game.cpp
    src/Game/GameUtils.cpp
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${FILE_IN})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_include_directories(${PROJECT_NAME} PRIVATE ${raylib_SOURCE_DIR}/src)

if(UNIX AND NOT APPLE)
    target_link_options(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)
endif()
