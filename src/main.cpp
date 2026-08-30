#include "raylib.h"

#include "menus/Game.hpp"
#include "menus/MainMenu.hpp"

#include "definitions.hpp"

int main()
{
    constexpr int screenWidth = 1000;
    constexpr int screenHeight = 1000;

    SetTraceLogLevel(LOG_ALL);

    Menu currentMenu = MAIN_MENU;

    InitWindow(screenWidth, screenHeight, "Added Difficulty");

    SetTargetFPS(144);
    SetExitKey(KEY_NULL);

    while (!WindowShouldClose()) {
        BeginDrawing();

        switch(currentMenu) {
            case MAIN_MENU:
                MainMenu::draw(Vector2{screenWidth, screenHeight});
                MainMenu::handle(currentMenu);
                break;
            case GAME:
                Game::draw(Vector2{screenWidth, screenHeight});
                Game::handle(currentMenu);
                break;
        }

        EndDrawing();
    }

    Game::end();
    CloseWindow();

    return 0;
}