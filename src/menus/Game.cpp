#include "Game.hpp"
#include "../AnimationModule.hpp"
#include "../Enemy.hpp"

namespace Game {
    static AnimHandler animHandler;

    static Texture2D player_texture_left;
    static Texture2D player_texture_right;
    static Texture2D badger;
    static FollowingEnemy testEnemy{1000, 1000, 2};

    static bool firstLoad = true;

    void draw(Vector2 resolution) {
        static Vector2 pos{};

        static bool looking_left = false;

        if (pos.x != GetMousePosition().x) {
            looking_left = pos.x > GetMousePosition().x;
        }

        pos = GetMousePosition();

        const float playerSize = resolution.x * 0.185;

        if (firstLoad) {
            player_texture_left = LoadTexture("assets/player_sprites_left.png");
            player_texture_right = LoadTexture("assets/player_sprites_right.png");
            badger = LoadTexture("assets/badger.png");

            testEnemy.speed = 4.0f;
            testEnemy.radius = resolution.x*0.1/2;

            firstLoad = false;
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


        // DrawTextureEx(
        //     badger,
        //     testEnemy.GetNextPosition(Vector2{pos.x, pos.y}, true, testEnemy.radius, testEnemy.radius),
        //     0.0f,
        //     0.5,
        //     WHITE
        // );

        testEnemy.DrawNextPos(badger, resolution.x*0.20/500, Vector2{pos.x, pos.y});
        testEnemy.DrawHitbox();
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
        UnloadTexture(badger);
    }
}