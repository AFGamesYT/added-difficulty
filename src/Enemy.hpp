#pragma once
#include <raylib.h>

class BaseEnemy {
protected:
    Rectangle hitbox{};
    float x{}, y{};
    int radius{};
    bool circleHitbox = false;
    double timeCreated;

public:
    explicit BaseEnemy(Rectangle hitbox);
    BaseEnemy(float x, float y, int radius);
    bool isCollidingRec(Rectangle rectangle);
};

class FollowingEnemy: public BaseEnemy {
public:
    float speed = 1.0;
    FollowingEnemy(float x, float y, int radius);
    Vector2 GetNextPosition(Vector2 target, bool set);
};