#pragma once

#include "Game2D.h"

namespace jm {
class GeometricObject {
protected:
    RGB color;
    vec2 pos;

    virtual void drawGeometric() const = 0;

public:
    GeometricObject() {}

    GeometricObject(const RGB &color, const vec2 &pos) : color(color), pos(pos)
    {
    }

    void draw()
    {
        beginTransformation();
        {
            translate(pos);
            drawGeometric();
        }
        endTransformation();
    }
};
}; // namespace jm
