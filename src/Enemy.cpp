#include "Enemy.hpp"
#include <cmath>
#include <algorithm>

BaseEnemy::BaseEnemy(Rectangle hitbox) {
    rectHitboxes.push_back(hitbox);

    timeCreated = GetTime();
    // we leave the hitbox type default
}

BaseEnemy::BaseEnemy(CircleParams hitbox) {
    circleHitboxes.push_back(hitbox);

    timeCreated = GetTime();
    hitboxType = Circle;
}

BaseEnemy::BaseEnemy(const std::vector<Rectangle>& hitboxes) {
    for (auto hitbox: hitboxes) {
        rectHitboxes.push_back(hitbox);
    }

    timeCreated = GetTime();
    hitboxType = Rect;
}

BaseEnemy::BaseEnemy(const std::vector<CircleParams>& hitboxes) {
    for (auto hitbox: hitboxes) {
        circleHitboxes.push_back(hitbox);
    }

    timeCreated = GetTime();
    hitboxType = Circle;
}

bool BaseEnemy::isCollidingRec(Rectangle rectangle) {
    if (hitboxType == Circle) {
        for (auto circle : circleHitboxes) {
            const double closestX = std::max(rectangle.x, std::min((float)circle.x, rectangle.x + rectangle.width));
            const double closestY = std::max(rectangle.y, std::min((float)circle.y, rectangle.y + rectangle.height));

            const double dx = circle.x - closestX;
            const double dy = circle.y - closestY;

            const bool touching = dx * dx + dy * dy <= circle.radius * circle.radius;

            if (!touching) continue;
            return true;
        }
        return false;
    }

    for (auto hitbox: rectHitboxes) {
        const bool touching = CheckCollisionRecs(hitbox, rectangle);
        if (!touching) continue;
        return true;
    }

    return false;
}

void BaseEnemy::DrawHitbox(Color color, int thickness) const {
    if (hitboxType == Circle) {
        for (auto circle: circleHitboxes) {
            DrawRing(Vector2{circle.x, circle.y}, circle.radius-thickness, circle.radius, 0, 360, 0, color);
        }
    } else {
        for (auto hitbox: rectHitboxes) {
            DrawLineEx(Vector2{hitbox.x, hitbox.y}, Vector2{hitbox.x + hitbox.width, hitbox.y}, thickness, color);
            DrawLineEx(Vector2{hitbox.x, hitbox.y}, Vector2{hitbox.x, hitbox.y+hitbox.height}, thickness, color);
            DrawLineEx(Vector2{hitbox.x, hitbox.y+hitbox.height}, Vector2{hitbox.x + hitbox.width, hitbox.y + hitbox.height}, thickness, color);
            DrawLineEx(Vector2{hitbox.x+hitbox.width, hitbox.y}, Vector2{hitbox.x + hitbox.width, hitbox.y + hitbox.height}, thickness, color);
        }
    }
}

void BaseEnemy::Draw(const Texture2D &texture, float scale) const {
    if (hitboxType == Circle) {
        for (auto circle: circleHitboxes) {
            const float newX = circle.x-2.0*circle.radius-0.5*scale*texture.width;
            const float newY = circle.y-2.0*circle.radius-0.5*scale*texture.width;
            DrawTextureEx(
                texture,
                Vector2{newX, newY},
                0,
                scale,
                WHITE
            );
        }
    }
}


void FollowingEnemy::DrawNextPos(double timeScale) {
    if (hitboxType == Circle) {
        for (auto &circle: circleHitboxes) {
            GetNextPosition(true, circle, timeScale);
            const float newX = circle.x-2.0*circle.radius;
            const float newY = circle.y-2.0*circle.radius;
            DrawTextureEx(
                texture,
                Vector2{newX, newY},
                0,
                textureScale,
                WHITE
            );
        }
    }
}

FollowingEnemy::FollowingEnemy(CircleParams params, Texture2D &texture) : BaseEnemy(params), texture(texture) {}

FollowingEnemy::FollowingEnemy(std::vector<CircleParams> params, Texture2D &texture) : BaseEnemy(params), texture(texture) {}

Vector2 FollowingEnemy::GetNextPosition(bool set, CircleParams &params, double timeScale) {
    const float dx = target.x - params.x;
    const float dy = target.y - params.y;

    const float dist = std::sqrt(dx * dx + dy * dy);

    if (dist <= speed) {
        if (set) {
            params.x = target.x;
            params.y = target.y;
        }

        return target;
    }

    const float nextX = params.x + dx / dist * speed * timeScale;
    const float nextY = params.y + dy / dist * speed * timeScale;

    if (set) {
        params.x = nextX;
        params.y = nextY;
    }

    return Vector2{nextX, nextY};
}

void FollowingEnemy::Update(double timeScale) {
    DrawNextPos(timeScale);
}

void DrawRectHitbox(Rectangle hitbox, Color color, int thickness) {
    DrawLineEx(Vector2{hitbox.x, hitbox.y}, Vector2{hitbox.x + hitbox.width, hitbox.y}, thickness, color);
    DrawLineEx(Vector2{hitbox.x, hitbox.y}, Vector2{hitbox.x, hitbox.y+hitbox.height}, thickness, color);
    DrawLineEx(Vector2{hitbox.x, hitbox.y+hitbox.height}, Vector2{hitbox.x + hitbox.width, hitbox.y + hitbox.height}, thickness, color);
    DrawLineEx(Vector2{hitbox.x+hitbox.width, hitbox.y}, Vector2{hitbox.x + hitbox.width, hitbox.y + hitbox.height}, thickness, color);
}

void DrawCircleHitbox(CircleParams circle, Color color, int thickness) {
    DrawRing(Vector2{circle.x, circle.y}, circle.radius-thickness, circle.radius, 0, 360, 0, color);
}