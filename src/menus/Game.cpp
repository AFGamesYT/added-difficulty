#include "Game.hpp"
#include "../AnimationModule.hpp"
#include "../Enemy.hpp"
#include "../definitions.hpp"

#include <vector>

namespace Game {
    // static variables
    static AnimHandler animHandler;

    // textures
    static Texture2D player_texture_left;
    static Texture2D player_texture_right;
    static Texture2D badger;

    static std::vector<BaseEnemy*> enemies;

    // enemy with multiple circle hitboxes

    static FollowingEnemy testEnemy{std::vector{
        CircleParams{1000, 1000, 2},
        CircleParams{0, 0, 2},
        CircleParams{1000, 0, 2}

    }, badger};

    // enemy with one circle

    // static FollowingEnemy testEnemy{CircleParams{1000, 1000, 2}, badger};

    static Rectangle playerRect;

    static bool firstLoad = true;
    static double gameOverTime;

    static float playerSize;
    static Vector2 finalPlayerPos;
    static bool looking_left = false;

    void draw(Vector2 resolution) {
        static Vector2 pos{};

        if (pos.x != GetMousePosition().x) {
            looking_left = pos.x > GetMousePosition().x;
        }

        pos = GetMousePosition();
        testEnemy.target = pos;

        if (firstLoad) {
            player_texture_left = LoadTexture("assets/player_sprites_left.png");
            player_texture_right = LoadTexture("assets/player_sprites_right.png");
            badger = LoadTexture("assets/badger.png");

            testEnemy.speed = 4.0f;
            for (auto &circle: testEnemy.circleHitboxes) {
                circle.radius = resolution.x*0.1/2;
            }
            testEnemy.circleHitboxes[1].radius = resolution.x*0.1/2;
            testEnemy.textureScale = resolution.x*0.20/500;

            enemies.push_back(&testEnemy);

            playerSize = resolution.x * 0.185;

            firstLoad = false;
        }

        ClearBackground(GAME_BG);

        animHandler.createSpriteAnim(1, 2, 500, 500, 0.7, true);
        playerRect = animHandler.spriteAnim(1);

        DrawTexturePro(
            looking_left ? player_texture_left : player_texture_right,
            playerRect,
            Rectangle{pos.x-playerSize/4, pos.y-playerSize/4, playerSize/2, playerSize/2},
            Vector2{0, 0},
            0.0f,
            WHITE);


        for (const auto enemy: enemies) {
            enemy->Update(1);
            enemy->DrawHitbox();  // draw hitbox for all enemies
        }
    }

    void handle(Menu &menu) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            menu = MAIN_MENU;
            ShowCursor();
        }
        const Vector2 pos = GetMousePosition();
        const auto playerHitbox = Rectangle{pos.x-playerSize/4, pos.y, playerSize/2, playerSize/4};
        DrawRectHitbox(playerHitbox);

        for (const auto enemy: enemies) {
            if (enemy->isCollidingRec(playerHitbox)) {
                gameOverTime = GetTime();
                menu = AFTER_GAME;
                finalPlayerPos = GetMousePosition();
                ShowCursor();
            }
        }
    }

    void afterGame(Menu &menu) {
            /* animation:
             * wait a bit
             * background fades to red
             * as that is happening, enemies slow down
             * player's cursor appears, but doesnt control the player
             * menu: " run finished - again / menu "
             */

        animHandler.createAnim(3, 1, 0, 1, 0);
        const double slow_progress = animHandler.quadraticOut(3);
        for (const auto enemy: enemies) {
            enemy->Update(slow_progress);
            enemy->DrawHitbox();
        }

        DrawTexturePro(
            looking_left ? player_texture_left : player_texture_right,
            playerRect,
            Rectangle{finalPlayerPos.x-playerSize/4, finalPlayerPos.y-playerSize/4, playerSize/2, playerSize/2},
            Vector2{0, 0},
            0.0f,
            WHITE);

        if (GetTime() - gameOverTime < 1.2) {
            ClearBackground(GAME_BG);
            return;
        }

        animHandler.createAnim(2, 0, 1, 3, 0);

        const double bg_progress = animHandler.linear(2);
        DrawRectangle(0, 0, 10000, 10000, Color{
            DEATH_BG.r,
            DEATH_BG.g,
            DEATH_BG.b,
            (unsigned char)(255*bg_progress),
        });
        DrawText("You died D:\nEnter to start again\nEsc to go to menu", 100, 100, 50, Color{
            WHITE.r,
            WHITE.g,
            WHITE.b,
            (unsigned char)(255*bg_progress),
        });

        if (IsKeyDown(KEY_ESCAPE)) {
            menu = MAIN_MENU;
        } else if (IsKeyPressed(KEY_ENTER)) {
            animHandler.stopAnim(2);
            // here we are going to need a restart function for future additions,
            // right now it works good enough like this
            menu = GAME;
        }
    }

    void end() {
        UnloadTexture(player_texture_left);
        UnloadTexture(player_texture_right);
        UnloadTexture(badger);
    }
}