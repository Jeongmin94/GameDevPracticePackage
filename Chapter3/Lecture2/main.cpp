#include "Examples/PrimitivesGallery.h"
#include "Game2D.h"
#include "RandomNumberGenerator.h"
#include "RigidCircle.h"
#include <memory>
#include <vector>

namespace jm {
class Example : public Game2D {
public:
    std::vector<RigidCircle *> rigidCircles;
    RandomNumberGenerator randGenerator;
    const float epsilon = 0.5f;

    Example() : Game2D() { reset(); }

    void reset()
    {
        if (!rigidCircles.empty()) {
            for (auto e : rigidCircles)
                delete e;
            rigidCircles.clear();
        }

        int num;
        std::cout << "생성할 공의 개수를 골라주세요: ";
        std::cin >> num;

        for (int i = 0; i < num; i++) {
            RigidCircle *rc = new RigidCircle();

            rc->color = Colors::gold;
            rc->pos = vec2(randGenerator.getFloat(-0.5f, 0.5f),
                           randGenerator.getFloat(0.3f, 1.0f));
            rc->vel = vec2(randGenerator.getFloat(1.0f, 10.0f), 0.0f);
            rc->radius = randGenerator.getFloat(0.1f, 0.2f);
            rc->mass = rc->radius * randGenerator.getFloat(1.0f, 1.3f);

            rigidCircles.push_back(rc);
        }
    }

    void drawWall()
    {
        setLineWidth(5.0f);
        drawLine(Colors::blue, {-1.0f, -1.0f}, Colors::blue, {1.0f, -1.0f});
        drawLine(Colors::blue, {1.0f, -1.0f}, Colors::blue, {1.0f, 1.0f});
        drawLine(Colors::blue, {-1.0f, -1.0f}, Colors::blue, {-1.0f, 1.0f});
    }

    void checkCollision(RigidCircle& a, RigidCircle& b)
    {
        // check in range
        const float distance = (a.pos - b.pos).getMagnitude();
        if (distance > a.radius + b.radius) {
            return;
        }

        // get rel and normal vector
        const auto rel_vel = a.vel - b.vel; // b에서 본 a의 상대 속도
        const auto normal =
            -(b.pos - a.pos) / (b.pos - a.pos).getMagnitude();      // b의 노말 벡터

        if (rel_vel.getDotProduct(normal) >= 0.0f) {
            return;
        }

        const auto impulse = normal * -(1.0f + epsilon) *
                             rel_vel.getDotProduct(normal) /
                             ((1.0f / a.mass) + (1.0f / b.mass));

        a.vel += impulse / a.mass;
        b.vel -= impulse / b.mass;
    }

    void update() override
    {
        const float dt = getTimeStep() * 0.4f;
        const int sz = rigidCircles.size();

        for (const auto &circle : rigidCircles) {
            circle->update(dt);
        }

        // physics update
        // 0번 공부터 n-1번 공까지 전부 비교해줘야됨
        for (int i = 0; i < sz; i++) {
            for (int j = i + 1; j < sz; j++) {
                // check collision and update
                checkCollision(*rigidCircles[i], *rigidCircles[j]);
            }
        }

        // draw
        drawWall();
        for (const auto &circle : rigidCircles) {
            circle->draw();
        }

        // reset button
        if (isKeyPressedAndReleased(GLFW_KEY_R)) {
            reset();
        }
    }
};
} // namespace jm

int main(void)
{
    jm::Example().run();

    return 0;
}
