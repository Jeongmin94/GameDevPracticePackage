#include "Star.h"

void jm::Star::drawGeometric() const
{
    drawFilledStar(color, outerRadius, innerRadius);
}
