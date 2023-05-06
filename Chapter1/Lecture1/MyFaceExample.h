#pragma once

#include "Game2D.h"

namespace jm {
class MyFaceExample : public Game2D {
private:
    float face = 0.8f;

public:
    void update() override;
};
} // namespace jm
