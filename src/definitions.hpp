#pragma once

enum Menu {
    MAIN_MENU,
    GAME,
    AFTER_GAME
};

enum HitboxType {
    Circle,
    Rect,
};

struct CircleParams {
    float x;
    float y;
    float radius;
};

constexpr Color GAME_BG = Color{12, 15, 33, 255};
constexpr Color DEATH_BG = Color{117, 23, 23, 255};