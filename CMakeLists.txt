cmake_minimum_required(VERSION 3.20)

project(AddedDifficulty)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
)

FetchContent_MakeAvailable(raylib)

add_executable(AddedDifficulty
        src/main.cpp
        src/AnimationModule.cpp
        src/menus/MainMenu.cpp
        src/menus/Game.cpp
        src/Enemy.cpp
)

target_link_libraries(AddedDifficulty PRIVATE raylib)

add_custom_command(TARGET AddedDifficulty POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:AddedDifficulty>/assets
)