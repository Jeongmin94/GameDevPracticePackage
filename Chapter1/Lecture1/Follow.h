#pragma once

#include "Game2D.h"

namespace jm {
class Follow : public Game2D {
private:
    const vec2 gun_pos;

    float getDegree(const float &radian) { return 180 / 3.141592f * radian; }

    void drawCenter() { drawFilledCircle(Colors::yellow, 0.2f); }

    void drawGun() { drawFilledBox(Colors::black, 0.3f, 0.075f); }

    void drawTurret(const vec2 &cursor)
    {
        rotate(getDegree(atan2(cursor.y, cursor.x)));
        drawCenter();

        translate(gun_pos);
        drawGun();
    }

public:

    Follow() : gun_pos(vec2(0.3f, 0.0f))
    {

    }

    void update() override
    {
        vec2 cursor = getCursorPos(true);
        drawTurret(cursor);
    }
};
} // namespace jm
