#pragma once

#include "Game2D.h"

namespace jm {
class BlueCircle : public Game2D {
private:
    const bool useScreen = true;
    const float radius = 0.2f;

    const vec2 top;
    const vec2 bottom;
    const vec2 left;
    const vec2 right;

public:
    BlueCircle()
        : top(0.0f, 0.18f), bottom(0.0f, -0.18f), left(-0.18f, 0.0f),
          right(0.18f, 0.0f)
    {
    }

    void drawCircle(const vec2 &cursor);

    void update() override;
};
} // namespace jm
