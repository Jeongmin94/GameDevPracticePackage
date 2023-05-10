#include "CursorStar.h"

void jm::CursorStar::drawStar(const vec2 &pos, const float &time)
{
    translate(pos);
    rotate(time * 90.0f);
    drawFilledStar(Colors::gold, 0.2f, 0.1f);
}

void jm::CursorStar::update()
{
    const vec2 pos = getCursorPos(true);
    drawStar(pos, time);
    time += getTimeStep();
}
