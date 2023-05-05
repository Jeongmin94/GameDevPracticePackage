#pragma once

#include "Game2D.h"

namespace jm {
class SolarSystem : public Game2D {
    float time = 0.0f;

public:
    void update() override
    {
        rotate(time * 60.0f);
        drawFilledStar(Colors::gold, 0.2f, 0.13f); // Sun

        rotate(time * 60.0f * 1.5f);
        translate(0.5f, 0.0f);
        drawFilledCircle(Colors::blue, 0.1f); // Earth

        rotate(time * 150.0f);
        translate(0.2f, 0.0f);
        drawFilledCircle(Colors::yellow, 0.05f); // Moon

        time += this->getTimeStep();
    }
};
} // namespace jm
