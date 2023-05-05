#pragma once

#include "Game2D.h"

namespace jm {
class SolarSystem : public Game2D {
    float time = 0.0f;

public:
    void update() override
    {
        const vec2 earth(0.5f, 0.0f);
        const vec2 moon(0.2f, 0.0f);

        beginTransformation();
        {
            rotate(time * 60.0f);
            drawFilledStar(Colors::gold, 0.2f, 0.13f); // Sun

            translate(earth);
            drawFilledStar(Colors::blue, 0.1f, 0.05f); // Earth

            rotate(time * 60.0f);
            translate(moon);
            drawFilledStar(Colors::yellow, 0.05f, 0.025f); // Moon
            endTransformation();
        }

        time += this->getTimeStep();
    }
};
} // namespace jm
