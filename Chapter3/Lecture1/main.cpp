#include "Examples/PrimitivesGallery.h"
#include "Game2D.h"
#include "RandomNumberGenerator.h"
#include <memory>
#include <vector>

namespace jm {
class RigidCircle {
public:
    vec2 pos;
    vec2 vel;
    float radius = 0.1f;

    void draw()
    {
        beginTransformation();
        {
            translate(pos);
            drawFilledCircle(Colors::hotpink, radius - 1e-3f);
            setLineWidth(2.0f);
            drawWiredCircle(Colors::black, radius);
        }
        endTransformation();
    }

    void update(const float &dt)
    {
        static const vec2 gravity = vec2(0.0f, -9.8f);
        // coefficient of restitution: 반발 계수
        static const float coef_res = 0.5f;
        static const float coef_friction = 0.99f;

        // numerical integration
        // 공이 이동하는 것을 표현하기 위해서는
        // 공이 가지고 있는 속도로 얼마 동안(시간) 이동했는지를 알아야 한다.
        // + 현실 세계의 중력을 표현하기 위해서는 속도에 중력을 포함시켜야 한다.
        vel += gravity * dt;
        pos += vel * dt;

        // wall collision, friction
        // 충돌 검사, 반응
        // 원의 경우 반지름과 벽의 거리를 비교해 충돌 처리 가능
        if (1.0f - pos.x <= radius) {
            pos.x = 1.0f - radius;

            if (vel.x >= 0.0f)
                vel.x *= -1.0f * coef_res;
        }

        if (pos.x - radius <= -1.0f)
        {
            pos.x = -1.0f + radius;

            if (vel.x <= 0)
                vel.x *= -1.0f * coef_res;
        }

        if (pos.y - radius <= -1.0f) {
            pos.y = -1.0f + radius;

            if (vel.y <= 0.0f)
                vel.y *= -1.0f * coef_res;

            vel.x *= coef_friction;
        }
    }
};

class Example : public Game2D {
public:
    RigidCircle rigid_body;

    Example() : Game2D() { reset(); }

    void reset()
    {
        // Initial position and velocity
        rigid_body.pos = vec2(-0.8f, 0.3f);
        rigid_body.vel = vec2(10.0f, 0.0f);
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
        // physics update
        rigid_body.update(getTimeStep() * 0.4f);

        // draw
        drawWall();
        rigid_body.draw();

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
