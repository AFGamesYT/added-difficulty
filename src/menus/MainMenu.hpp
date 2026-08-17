#pragma once
#include <raylib.h>

#include "../definitions.hpp"

namespace MainMenu {
    void draw(Vector2 resolution);

    void handle(Menu &menu);
}