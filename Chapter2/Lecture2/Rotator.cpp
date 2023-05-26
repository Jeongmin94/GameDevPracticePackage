#include "Rotator.h"

void jm::Rotator::rotateObject(GeometricObject *go, const float &speed)
{
    beginTransformation();
    {
        translate(go->getPos());
        rotate(getRadian(time * 360.0 * speed));
        go->drawGeometric();
    }
    endTransformation();

    time += getTimeStep();
}
