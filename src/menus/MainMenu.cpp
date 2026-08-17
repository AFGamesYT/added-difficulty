#include "MainMenu.hpp"

namespace MainMenu {
    void draw(Vector2 resolution) {
        ClearBackground(RAYWHITE);

        DrawText("Main Menu\nPress Enter for red square", 100, 100, 50, BLACK);
    }

    void handle(Menu &menu) {
        if (IsKeyPressed(KEY_ENTER)) {
            menu = GAME;
            HideCursor();
        }
    }
}