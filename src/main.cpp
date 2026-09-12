#include "raylib.h"

#include "menus/Game.hpp"
#include "menus/MainMenu.hpp"

#include "definitions.hpp"

// change this after adding settings
// load from file
Vector2 resolution = {1000, 1000};

int main()
{
    // sourGummy = LoadFont("assets/SourGummy_font.ttf");

    SetTraceLogLevel(LOG_ALL);

    Menu currentMenu = MAIN_MENU;

    InitWindow(resolution.x, resolution.y, "Added Difficulty");

    SetTargetFPS(144);
    SetExitKey(KEY_NULL);

    while (!WindowShouldClose()) {
        BeginDrawing();

        switch(currentMenu) {
            case MAIN_MENU:
                MainMenu::draw();
                MainMenu::handle(currentMenu);
                break;
            case GAME:
                Game::draw();
                Game::handle(currentMenu);
                break;
            case AFTER_GAME:
                Game::afterGame(currentMenu);
        }

        EndDrawing();
    }

    Game::end();
    MainMenu::end();

    CloseWindow();

    return 0;
}