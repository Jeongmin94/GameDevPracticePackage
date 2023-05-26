#pragma once

#include "GeometricObject.h"

namespace jm {
class Box : public GeometricObject {
private:
    const float width;
    const float height;

protected:
    void drawGeometric() const override;

public:
    Box(const RGB &color, const vec2 &pos, const float &width,
        const float &height)
        : GeometricObject(color, pos), width(width), height(height)
    {
    }
};
}; // namespace jm
