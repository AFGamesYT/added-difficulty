#pragma once
#include <raylib.h>

class BaseEnemy {
protected:
    Rectangle hitbox{};
    float x{}, y{};
    bool circleHitbox = false;
    double timeCreated;

public:
    int radius{};
    explicit BaseEnemy(Rectangle hitbox);
    BaseEnemy(float x, float y, int radius);
    bool isCollidingRec(Rectangle rectangle);
    void DrawHitbox(Color color = RED, int thickness = 1) const;
    void Draw(const Texture2D &texture, float scale) const;
};

class FollowingEnemy: public BaseEnemy {
public:
    float speed = 1.0;
    FollowingEnemy(float x, float y, int radius);
    Vector2 GetNextPosition(Vector2 target, bool set, float offsetX = 0, float offsetY = 0);
    void DrawNextPos(const Texture2D &texture, float scale, Vector2 target);
};