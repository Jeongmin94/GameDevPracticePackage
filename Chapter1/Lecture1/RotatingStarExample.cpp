#include "RotatingStarExample.h"

namespace jm {
void RotatingStarExample::update()
{
    float outer = 0.5f;
    float inner = 0.25f;

    rotate(time * 60.0f * 3.0f);
    drawFilledStar(Colors::gold, outer, inner);

    time += getTimeStep();
}
} // namespace jm
