#pragma once

#include "GeometricObject.h"

namespace jm {
class Star : public GeometricObject {
private:
    const float innerRadius;
    const float outerRadius;

protected:
    void drawGeometric() const override;

public:
    Star(const RGB &color, const vec2 &pos, const float &outerRadius,
         const float &innerRadius)
        : GeometricObject(color, pos), outerRadius(outerRadius),
          innerRadius(innerRadius)
    {
    }
};
}; // namespace jm
