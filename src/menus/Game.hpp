#pragma once
#include <raylib.h>
#include <vector>

#include "../definitions.hpp"
#include "../Enemy.hpp"

namespace Game {
    void draw();

    void handle(Menu &menu);

    void afterGame(Menu &menu);

    void end();
}