cmake_minimum_required(VERSION 3.20)

project(AddedDifficulty)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(AddedDifficulty
        src/main.cpp
        src/AnimationModule.cpp
        src/menus/MainMenu.cpp
        src/menus/Game.cpp
        src/Enemy.cpp
)

find_package(raylib REQUIRED)

target_link_libraries(AddedDifficulty PRIVATE raylib)

add_custom_command(TARGET AddedDifficulty POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:AddedDifficulty>/assets
)