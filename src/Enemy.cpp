#include "Enemy.hpp"
#include <cmath>

Enemy::Enemy(Rectangle hitbox)
    : hitbox(hitbox)
{
    timeCreated = GetTime();
}

Enemy::Enemy(int x, int y, int radius)
    : x(x), y(y), radius(radius)
{
    timeCreated = GetTime();
    circleHitbox = true;
}

bool Enemy::isCollidingRec(Rectangle rectangle) {
    if (circleHitbox) {
        const double closestX = std::max(rectangle.x, std::min((float)x, rectangle.x + rectangle.width));
        const double closestY = std::max(rectangle.y, std::min((float)y, rectangle.y + rectangle.height));

        const double dx = x - closestX;
        const double dy = x - closestY;

        return dx * dx + dy * dy <= radius * radius;

    }

    return CheckCollisionRecs(hitbox, rectangle);
}