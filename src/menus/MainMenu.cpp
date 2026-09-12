#include "MainMenu.hpp"

#include "../definitions.hpp"

namespace MainMenu {
    static Font font;
    static bool firstLoad = true;
    void draw(Vector2 resolution) {
        ClearBackground(RAYWHITE);

        if (firstLoad) {
            font = LoadFontEx("assets/SourGummy_font.ttf", (int)(0.07*resolution.y), nullptr, 0);
            firstLoad = false;
        }

        // DrawText("Main Menu\nPress Enter to start the game", 100, 100, 50, BLACK);
        DrawTextEx(font, "Main Menu\n\nPress Enter to start the game", Vector2{100, 100}, (float)(0.07*resolution.y), 0, BLACK);
    }

    void handle(Menu &menu) {
        if (IsKeyPressed(KEY_ENTER)) {
            menu = GAME;
            HideCursor();
        }
    }

    void end() {
        UnloadFont(font);
    }
}