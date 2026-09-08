#pragma once
#include <raylib.h>
#include <vector>

#include "../definitions.hpp"
#include "../Enemy.hpp"

namespace Game {
    void draw(Vector2 resolution);

    void handle(Menu &menu);

    void afterGame(Menu &menu);

    void end();
}