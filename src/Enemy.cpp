#include "Enemy.hpp"
#include <cmath>

BaseEnemy::BaseEnemy(Rectangle hitbox)
    : hitbox(hitbox)
{
    timeCreated = GetTime();
}

BaseEnemy::BaseEnemy(float x, float y, int radius)
    : x(x), y(y), radius(radius)
{
    timeCreated = GetTime();
    circleHitbox = true;
}

bool BaseEnemy::isCollidingRec(Rectangle rectangle) {
    if (circleHitbox) {
        const double closestX = std::max(rectangle.x, std::min((float)x, rectangle.x + rectangle.width));
        const double closestY = std::max(rectangle.y, std::min((float)y, rectangle.y + rectangle.height));

        const double dx = x - closestX;
        const double dy = x - closestY;

        return dx * dx + dy * dy <= radius * radius;
    }
    return CheckCollisionRecs(hitbox, rectangle);
}

FollowingEnemy::FollowingEnemy(float x, float y, int radius) : BaseEnemy(x, y, radius) {}

Vector2 FollowingEnemy::GetNextPosition(Vector2 target, bool set, float offsetX, float offsetY) {
    const float dx = target.x - x;
    const float dy = target.y - y;

    const float dist = std::sqrt(dx * dx + dy * dy);

    if (dist <= speed) {
        if (set) {
            x = target.x;
            y = target.y;
        }

        return target;
    }

    const float nextX = x + dx / dist * speed;
    const float nextY = y + dy / dist * speed;

    if (set) {
        x = nextX;
        y = nextY;
    }

    return Vector2{nextX-offsetX, nextY-offsetY};
}

void BaseEnemy::DrawHitbox(Color color, int thickness) const {
    if (circleHitbox) {
        DrawRing(Vector2{x, y}, (float)(radius-thickness), (float)radius, 0, 360, 0, color);
    }
}

void BaseEnemy::Draw(const Texture2D &texture, float scale) const {
    if (circleHitbox) {
        const float newX = x-2.0*radius-0.5*scale*texture.width;
        const float newY = y-2.0*radius-0.5*scale*texture.width;
        DrawTextureEx(
            texture,
            Vector2{newX, newY},
            0,
            scale,
            WHITE
        );
    }
}

void FollowingEnemy::DrawNextPos(const Texture2D &texture, float scale, Vector2 target) {
    GetNextPosition(target, true);
    if (circleHitbox) {
        const float newX = x-2.0*radius;
        const float newY = y-2.0*radius;
        DrawTextureEx(
            texture,
            Vector2{newX, newY},
            0,
            scale,
            WHITE
        );
    }
}