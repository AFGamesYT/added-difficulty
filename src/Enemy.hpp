#pragma once
#include <raylib.h>
#include "definitions.hpp"
#include <vector>

class BaseEnemy {
protected:
    HitboxType hitboxType = Rect; // default is Rect
public:
    double timeCreated;

    std::vector<Rectangle> rectHitboxes{};
    std::vector<CircleParams> circleHitboxes{};

    virtual ~BaseEnemy() = default;

    explicit BaseEnemy(Rectangle hitbox);
    explicit BaseEnemy(CircleParams hitbox);
    explicit BaseEnemy(const std::vector<Rectangle>& hitboxes);
    explicit BaseEnemy(const std::vector<CircleParams>& hitboxes);

    bool isCollidingRec(Rectangle rectangle);

    void DrawHitbox(Color color = RED, int thickness = 1) const;
    void Draw(const Texture2D &texture, float scale) const;

    virtual void Update() = 0;
};

class FollowingEnemy: public BaseEnemy {
public:
    float speed = 1;
    Vector2 target{};
    float textureScale = 1;
    Texture2D &texture;

    explicit FollowingEnemy(CircleParams params, Texture2D &texture);
    explicit FollowingEnemy(std::vector<CircleParams> params, Texture2D &texture);

    Vector2 GetNextPosition(bool set, CircleParams &params);
    void DrawNextPos();

    void Update() override;
};

class SwitchVerticalLines: public BaseEnemy {
public:
    float switchSpeed = 1;
    SwitchVerticalLines(Rectangle hitbox);
};

void DrawRectHitbox(Rectangle rect, Color color = RED, int thickness = 1);
void DrawCircleHitbox(CircleParams circle, Color color = RED, int thickness = 1);
