#pragma once

#include "Game2D.h"
#include "DrawFunctions.h"

namespace jm {
class RotatingStarExample : public Game2D {
private:
    float time = 0.0f;

public:
    void update() override;
};
} // namespace jm