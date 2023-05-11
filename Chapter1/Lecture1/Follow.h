#pragma once

#include "Game2D.h"

namespace jm {
class Follow : public Game2D {
private:
    vec2 center = vec2(0.0f, 0.0f);
    void drawDirection(const vec2 &cursor)
    {
        //translate(center);

        float d = atan2f(cursor.y, cursor.x);
        rotate(180 / 3.141592f * (d));
        drawFilledBox(Colors::yellow, 0.4f, 0.02f);
    }

public:
    void update() override
    {
        vec2 cursor = getCursorPos(true);
        drawDirection(cursor);
    }
};
} // namespace jm
