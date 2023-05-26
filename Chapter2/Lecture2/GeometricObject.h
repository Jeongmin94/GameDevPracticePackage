#pragma once

#include "Game2D.h"

namespace jm {
class GeometricObject {
private:
    float time = 0.0f;

protected:
    RGB color;
    vec2 pos;

    void rotateObj(const float &speed)
    {
        rotate(getRadian(time * 360.0 * speed));
    }

public:
    GeometricObject() {}

    GeometricObject(const RGB &color, const vec2 &pos) : color(color), pos(pos)
    {
    }

    virtual void drawGeometric() const = 0;

    void draw()
    {
        beginTransformation();
        {
            translate(pos);
            drawGeometric();
        }
        endTransformation();
    }

    vec2 &getPos() { return pos; }
};
}; // namespace jm
