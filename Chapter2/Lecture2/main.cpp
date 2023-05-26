#include "Circle.h"
#include "Examples/PrimitivesGallery.h"
#include "Game2D.h"
#include "GeometricObject.h"
#include "RandomNumberGenerator.h"
#include "Triangle.h"
#include "Box.h"
#include "Star.h"

namespace jm {
class Example : public Game2D {
public:
    Example() : Game2D() {}

    Triangle t{Colors::black, vec2(-0.3f, 0.0f), 0.3f};
    Circle c{Colors::gold, vec2(0.3f, 0.0f), 0.3f};
    Box b{Colors::blue, vec2(0.5f, 0.3f), 0.25f, 0.3f};
    Star s{Colors::gray, vec2(0.3f, 0.0f), 0.2f, 0.12f};

    Rotator rotator;

    void update() override
    {
        rotator.rotateObject(&b, 3.0f);
        s.draw();
    }
};
} // namespace jm

int main(void)
{
    jm::Example().run();
    return 0;
}
