#pragma once
#include <raylib.h>
#include "definitions.hpp"
#include <vector>

class BaseEnemy {
protected:
    HitboxType hitboxType = Rect; // default is Rect
public:
    double timeCreated;

    bool disabled = false;

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

    virtual void Update(double timeScale) = 0;
};

class FollowingEnemy: public BaseEnemy {
public:
    float speed = 1;
    Vector2 target{};
    float textureScale = 1;
    Texture2D &texture;

    explicit FollowingEnemy(CircleParams params, Texture2D &texture);
    explicit FollowingEnemy(const std::vector<CircleParams>& params, Texture2D &texture);

    Vector2 GetNextPosition(bool set, CircleParams &params, double timeScale);
    void DrawNextPos(double timeScale);

    void Update(double timeScale) override;
};

class SwitchVerticalLines: public BaseEnemy {
public:
    float switchTime = 3;
    float nothingTime = 1.5; // time before switch time where there are no hitboxes
    double timeCreated;
    double timeSwitched{};
    explicit SwitchVerticalLines(const std::vector<Rectangle> &hitboxes);

    void Update(double timeScale) override;

    void Draw(Color color) const;
};

std::vector<Rectangle> generateVerticalLinesHitboxes(int lines);
void DrawRectHitbox(Rectangle rect, Color color = RED, int thickness = 1);
void DrawCircleHitbox(CircleParams circle, Color color = RED, int thickness = 1);
