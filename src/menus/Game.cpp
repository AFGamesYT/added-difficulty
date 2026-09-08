#include "Game.hpp"
#include "../AnimationModule.hpp"
#include "../Enemy.hpp"
#include "../definitions.hpp"

namespace Game {
    // static variables
    static AnimHandler animHandler;

    static Texture2D player_texture_left;
    static Texture2D player_texture_right;
    static Texture2D badger;

    static FollowingEnemy testEnemy{CircleParams{1000, 1000, 2}};

    static Rectangle playerRect;

    static bool firstLoad = true;
    static bool ggs = false;

    static float playerSize;

    void draw(Vector2 resolution) {
        static Vector2 pos{};

        static bool looking_left = false;

        if (pos.x != GetMousePosition().x) {
            looking_left = pos.x > GetMousePosition().x;
        }

        pos = GetMousePosition();


        if (firstLoad) {
            player_texture_left = LoadTexture("assets/player_sprites_left.png");
            player_texture_right = LoadTexture("assets/player_sprites_right.png");
            badger = LoadTexture("assets/badger.png");

            testEnemy.speed = 4.0f;
            testEnemy.radius = resolution.x*0.1/2;

            playerSize = resolution.x * 0.185;

            firstLoad = false;
        }

        ClearBackground(!ggs ? GAME_BG : DEATH_BG);

        animHandler.createSpriteAnim(1, 2, 500, 500, 0.7, true);
        playerRect = animHandler.spriteAnim(1);

        DrawTexturePro(
            looking_left ? player_texture_left : player_texture_right,
            playerRect,
            Rectangle{pos.x-playerSize/4, pos.y-playerSize/4, playerSize/2, playerSize/2},
            Vector2{0, 0},
            0.0f,
            WHITE);


        testEnemy.DrawNextPos(badger, resolution.x*0.20/500, Vector2{pos.x, pos.y});
        testEnemy.DrawHitbox();
    }

    void handle(Menu &menu) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            menu = MAIN_MENU;
            ShowCursor();
        }
        const Vector2 pos = GetMousePosition();
        const auto playerHitbox = Rectangle{pos.x-playerSize/4, pos.y, playerSize/2, playerSize/4};
        DrawRectHitbox(playerHitbox);

        if (testEnemy.isCollidingRec(playerHitbox)) {
            /* animation:
             * background fades to red
             * as that is happening, enemies slow down
             * player's cursor appears, but doesnt control the player
             * menu: " run finished - again / menu "
             */

            ggs = true;
            menu = AFTER_GAME;
        }
    }

    void afterGame(Menu &menu) {
        ClearBackground(DEATH_BG);
        DrawText("You died D:\nEnter to start again\nEsc to go to menu", 100, 100, 50, WHITE);
        if (IsKeyDown(KEY_ESCAPE)) {
            menu = MAIN_MENU;
        } else if (IsKeyPressed(KEY_ENTER)) {
            ggs = false;
            // here we need a restart function for future additions,
            // right now its perfectly fine like this
            menu = GAME;
        }
    }

    void end() {
        UnloadTexture(player_texture_left);
        UnloadTexture(player_texture_right);
        UnloadTexture(badger);
    }
}