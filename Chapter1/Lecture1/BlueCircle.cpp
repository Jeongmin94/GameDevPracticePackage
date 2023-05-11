#include "BlueCircle.h"

void jm::BlueCircle::drawCircle(const vec2 &cursor)
{
    if (left.x <= cursor.x && cursor.x <= right.x && bottom.y <= cursor.y &&
        cursor.y <= top.y) {
        drawFilledCircle(Colors::red, radius);
    }
    else {
        drawFilledCircle(Colors::blue, radius);
    }
}

void jm::BlueCircle::update()
{
    const vec2 cursor = getCursorPos(useScreen);
    std::cout << cursor.x << ' ' << cursor.y << std::endl;
    drawCircle(cursor);
}
