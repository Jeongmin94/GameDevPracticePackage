#pragma once

#include "Game2D.h"

namespace jm {
class MyFaceExample : public Game2D {
private:
    float face = 0.8f;
    float time = 0.0f;
    float eyes_outer_radian = 0.2f;
    float eyes_inner_radian = 0.1f;

public:
    void update() override;
};
} // namespace jm
