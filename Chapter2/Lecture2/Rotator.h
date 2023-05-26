#pragma once

#include "Game2D.h"
#include "GeometricObject.h"

namespace jm {
class Rotator : public Game2D {
private:
    const vec2 origin{0.0f, 0.0f};
    float time = 0.0f;

public:
    void rotateObject(GeometricObject *go, const float &speed);
};
}; // namespace jm
