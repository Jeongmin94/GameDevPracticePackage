#pragma once

#include "GeometricObject.h"
#include "Rotator.h"

namespace jm {
class Star : public GeometricObject, Rotator {
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
