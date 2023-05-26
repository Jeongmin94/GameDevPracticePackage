#pragma once

#include "GeometricObject.h"

namespace jm {
class Circle : public GeometricObject {
private:
    const float radius;

protected:
    void drawGeometric() const override;

public:
    Circle(const RGB &color, const vec2 &pos, const float &radius)
        : GeometricObject(color, pos), radius(radius)
    {
    }
};
}; // namespace jm
