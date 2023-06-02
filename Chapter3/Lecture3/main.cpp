#include "Examples/PrimitivesGallery.h"
#include "Game2D.h"
#include "RandomNumberGenerator.h"
#include "RigidCircle.h"
#include <memory>
#include <vector>

namespace jm {
class Example : public Game2D {
public:
    RigidCircle rb0, rb1;

    Example() : Game2D() { reset(); }

    void reset()
    {
        // Initial position and velocity
        rb0.pos = vec2(0.0f, 0.5f);
        rb0.vel = vec2(0.0f, 0.0f);
        rb0.color = Colors::hotpink;
        rb0.radius = 0.03f;
        rb0.mass = 1.0f;

        rb1.pos = vec2(0.5f, 0.5f);
        rb1.vel = vec2(0.0f, 0.0f);
        rb1.color = Colors::yellow;
        rb1.radius = 0.03f;
        rb1.mass = rb0.mass * std::pow(rb1.radius / rb0.radius, 2.0f);
    }

    void drawWall()
    {
        setLineWidth(5.0f);
        drawLine(Colors::blue, {-1.0f, -1.0f}, Colors::blue, {1.0f, -1.0f});
        drawLine(Colors::blue, {1.0f, -1.0f}, Colors::blue, {1.0f, 1.0f});
        drawLine(Colors::blue, {-1.0f, -1.0f}, Colors::blue, {-1.0f, 1.0f});
    }

    void update() override
    {
        const float dt = getTimeStep() * 0.4f;
        const float epsilon = 0.5f;

        // physics update (Temporarily disabled)
        // rb0.update(dt);
        // rb1.update(dt);

        // coefficients
        const vec2 gravity(0.0f, -9.8f);
        const float l0 = 0.5f;
        const float coeff_k = 100.0f;       // 용수철의 힘
        const float coeff_d = 100.0f;       // 댐퍼의 힘

        // update rb1 (Note: rb0 is fixed)
        {
            // 스프링의 힘은 초기 스프링의 길이와 두 질점 사이 거리에 비례한다.
            const auto distance = (rb1.pos - rb0.pos).getMagnitude();
            const auto direction = (rb1.pos - rb0.pos) / distance;

            // compute stiffness force
            // + compute damping force
            const auto spring_force =
                direction * -(distance - l0) * coeff_k +
                direction * -((rb1.vel - rb0.vel).getDotProduct(direction)) *
                    coeff_d;


            const auto accel = gravity + spring_force / rb1.mass;

            rb1.vel += accel * dt;
            rb1.pos += rb1.vel * dt;
        }

        // draw
        drawWall();

        // spring
        drawLine(Colors::red, rb0.pos, Colors::red, rb1.pos);

        // mass points
        rb0.draw();
        rb1.draw();

        // reset button
        if (isKeyPressedAndReleased(GLFW_KEY_R))
            reset();
    }
};
} // namespace jm

int main(void)
{
    jm::Example().run();

    return 0;
}
