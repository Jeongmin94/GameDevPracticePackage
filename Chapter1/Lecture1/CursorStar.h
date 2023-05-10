#pragma once

#include "Game2D.h"

namespace jm {
class CursorStar : public Game2D {
private:
    float time;

public:
    void drawStar(const vec2 &pos, const float &time);

    void update() override;
};
} // namespace jm