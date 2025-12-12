cmake_minimum_required(VERSION 3.24)

project(uwurg)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(USE_STATIC_LIBS ON CACHE BOOL "" FORCE)
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
set(PLATFORM Desktop)

if(NOT WIN32)
    add_compile_options(-Wall -Wextra -pedantic)
endif()

FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
    URL_HASH ""
)

FetchContent_MakeAvailable(raylib)

set(FILE_IN
    src/TextureManager/TextureManager.cpp
    src/ObjectManager/ObjectManager.cpp
    src/SoundManager/SoundManager.cpp
    src/ManagedSound/ManagedSound.cpp
    src/Shaders/ShadersManager.cpp
    src/Window/Window.cpp
    src/Object/Object.cpp
    src/Game/Game.cpp
    src/Game/GameUtils.cpp
    src/Game/GamePlay.cpp
    src/Game/GameBot.cpp
    src/State/State.cpp
    src/main.cpp
)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(DEBUG_MODE)
endif()

if(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${FILE_IN})
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
else()
    add_executable(${PROJECT_NAME} ${FILE_IN})
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_include_directories(${PROJECT_NAME} PRIVATE ${raylib_SOURCE_DIR}/src)

if(UNIX AND NOT APPLE)
    target_link_options(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)
endif()

# Add the tests subdirectory
add_subdirectory(tests)
