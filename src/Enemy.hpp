#pragma once
#include <raylib.h>
#include "definitions.hpp"

class BaseEnemy {
protected:
    Rectangle hitbox{};
    float x{}, y{};
    bool circleHitbox = false;
    double timeCreated;

public:
    float radius{};
    explicit BaseEnemy(Rectangle hitbox);
    BaseEnemy(CircleParams params);
    bool isCollidingRec(Rectangle rectangle);
    void DrawHitbox(Color color = RED, int thickness = 1) const;
    void Draw(const Texture2D &texture, float scale) const;
};

class FollowingEnemy: public BaseEnemy {
public:
    float speed = 1.0;
    FollowingEnemy(CircleParams params);
    Vector2 GetNextPosition(Vector2 target, bool set, float offsetX = 0, float offsetY = 0);
    void DrawNextPos(const Texture2D &texture, float scale, Vector2 target);
};

void DrawRectHitbox(Rectangle rect, Color color = RED, int thickness = 1);
void DrawCircleHitbox(CircleParams circle, Color color = RED, int thickness = 1);
