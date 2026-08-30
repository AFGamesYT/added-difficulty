#pragma once
#include <raylib.h>

class Enemy {
    Rectangle hitbox{};
    int x{}, y{}, radius{};
    bool circleHitbox = false;
    double timeCreated;

public:
    explicit Enemy(Rectangle hitbox);
    Enemy(int x, int y, int radius);
    bool isCollidingRec(Rectangle rectangle);
};
