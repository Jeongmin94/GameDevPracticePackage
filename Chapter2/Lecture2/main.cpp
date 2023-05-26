#include "Circle.h"
#include "Examples/PrimitivesGallery.h"
#include "Game2D.h"
#include "GeometricObject.h"
#include "RandomNumberGenerator.h"
#include "Triangle.h"
#include "Box.h"
#include "Star.h"
#include "Mouse.h"

namespace jm {
class Example : public Game2D {
public:
    Example() : Game2D() {}

    Star s{Colors::gold, vec2(0.3f, 0.0f), 0.2f, 0.12f};

    Rotator rotator;

    void update() override
    {
        rotator.rotateObject(&s, 3.0f);
    }
};
} // namespace jm

int main(void)
{
    jm::Mouse().run();
    return 0;
}
