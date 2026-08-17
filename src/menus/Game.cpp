#include "Game.hpp"

namespace Game {
    void draw(Vector2 resolution) {
        Vector2 playerPos = GetMousePosition();

        ClearBackground(RAYWHITE);

        DrawRectangle(playerPos.x-25, playerPos.y-25, 50, 50, RED);
    }

    void handle(Menu &menu) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            menu = MAIN_MENU;
            ShowCursor();
        }

    }
}