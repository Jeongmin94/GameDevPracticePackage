#pragma once

#include "Game2D.h"

namespace jm {
class TransformationExample : public Game2D {
private:
    float time = 0.0f;

public:
    void rotateBox();

    void update() override { rotateBox(); }
};
} // namespace jm