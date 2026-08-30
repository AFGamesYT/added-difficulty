#include "Game.hpp"
#include "../AnimationModule.hpp"

namespace Game {
    static AnimHandler animHandler;

    static Texture2D player_texture_left;
    static Texture2D player_texture_right;

    static bool loadedTextures = false;

    void draw(Vector2 resolution) {
        static Vector2 pos{};

        static bool looking_left = false;

        if (pos.x != GetMousePosition().x) {
            looking_left = pos.x > GetMousePosition().x;
        }

        pos = GetMousePosition();

        const float playerSize = resolution.x * 0.185;

        if (!loadedTextures) {
            player_texture_left = LoadTexture("assets/player_sprites_left.png");
            player_texture_right = LoadTexture("assets/player_sprites_right.png");

            loadedTextures = true;
        }

        ClearBackground(Color{12, 15, 33, 255});

        animHandler.createSpriteAnim(1, 2, 500, 500, 0.7, true);
        const Rectangle playerRect = animHandler.spriteAnim(1);

        DrawTexturePro(
            looking_left ? player_texture_left : player_texture_right,
            playerRect,
            Rectangle{pos.x-playerSize/2, pos.y-playerSize/2, playerSize/2, playerSize/2},
            Vector2{0, 0},
            0.0f,
            WHITE);
    }

    void handle(Menu &menu) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            menu = MAIN_MENU;
            ShowCursor();
        }
    }

    void end() {
        UnloadTexture(player_texture_left);
        UnloadTexture(player_texture_right);
    }
}