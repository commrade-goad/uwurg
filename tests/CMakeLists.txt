cmake_minimum_required(VERSION 3.20)

project(uwurg_tests CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include project headers
include_directories(${CMAKE_SOURCE_DIR}/src)

set(TEST_SOURCES
    main.cpp
    GameEnums.cpp
    Object.cpp
    ObjectManager.cpp
    TextureManager.cpp
    SoundManager.cpp
    State.cpp
    ShaderManager.cpp
    ../src/TextureManager/TextureManager.cpp
    ../src/ObjectManager/ObjectManager.cpp
    ../src/SoundManager/SoundManager.cpp
    ../src/ManagedSound/ManagedSound.cpp
    ../src/Shaders/ShadersManager.cpp
    ../src/Window/Window.cpp
    ../src/Object/Object.cpp
    ../src/Game/Game.cpp
    ../src/Game/GameUtils.cpp
    ../src/Game/GamePlay.cpp
    ../src/Game/GameBot.cpp
    ../src/State/State.cpp
)

add_executable(uwurg_tests ${TEST_SOURCES})

# Link the raylib target provided by root FetchContent
target_link_libraries(uwurg_tests PRIVATE raylib)
