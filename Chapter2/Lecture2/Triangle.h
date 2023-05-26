#pragma once

#include "GeometricObject.h"

namespace jm {
class Triangle : public GeometricObject {
private:
    const float length;

protected:
    void drawGeometric() const override;

public:
    Triangle(const RGB &color, const vec2 &pos, const float &length)
        : GeometricObject(color, pos), length(length)
    {
    }
};
}; // namespace jm
