#include "Examples/PrimitivesGallery.h"
#include "Game2D.h"
#include "House.h"
#include "RandomNumberGenerator.h"

namespace jm {
class Example : public Game2D {
public:
    float time = 0.0f;
    House houses[10];
    RandomNumberGenerator rand;

    Example()
    {
        // initHouse
        for (int i = 0; i < 10; i++) {
            if (i % 2 == 0) {
                houses[i].setWindow();
            }
            houses[i].setPos(
                vec2(rand.getFloat(-0.5f, 0.5f), rand.getFloat(-0.5f, 0.5f)));

            houses[i].setRotateSpeed(rand.getFloat(1.0f, 20.0f));
        }
    }

    void update() override
    {
        for (int i = 0; i < 10; i++) {
            houses[i].draw(time);
        }

        time += getTimeStep();
    }
};
} // namespace jm

int main(void)
{
    jm::Example().run();
    // jm::Game2D().init("This is my digital canvas!", 1280, 960, false).run();
    // jm::PrimitivesGallery().run();

    return 0;
}
