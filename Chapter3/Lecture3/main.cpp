#include "Examples/PrimitivesGallery.h"
#include "Game2D.h"
#include "RandomNumberGenerator.h"
#include "RigidCircle.h"
#include <memory>
#include <vector>

namespace jm {
class Example : public Game2D {
private:
    const RGB stickColor = Colors::yellow;
    const RGB moveColor = Colors::blue;

    const float circleRadius = 0.03f;
    const float circleMass = 1.0f;

    void clearBalls(const std::vector<std::vector<RigidCircle *>> balls)
    {
        if (!balls.empty()) {
            for (int i = 0; i < balls.size(); i++) {
                for (int j = 0; j < balls[i].size(); j++) {
                    if (balls[i][j])
                        delete balls[i][j];
                }
            }
        }
    }

    void initBalls(std::vector<std::vector<RigidCircle *>> &balls)
    {
        balls.resize(4);
        for (int i = 0; i < balls.size(); i++) {
            balls[i].resize(4);
        }
    }

    void createBalls(std::vector<std::vector<RigidCircle *>> &balls)
    {
        const float dist = 0.4f;
        float y = 0.8f;

        auto mass = circleMass;
        for (int i = 0; i < 4; i++) {
            if (i != 0)
            {
                mass *= i;
            }
            float x = -0.6f;
            for (int j = 0; j < 4; j++) {
                if ((i == 0 && j == 0) || (i == 0 && j == 3)) {
                    balls[i][j] =
                        new RigidCircle(vec2(x, y), vec2(0.0f, 0.0f),
                                        stickColor, circleRadius, circleMass);
                }
                else {
                    balls[i][j] =
                        new RigidCircle(vec2(x, y), vec2(0.0f, 0.0f), moveColor,
                                        circleRadius, mass);
                }
                x += dist;
            }
            y -= dist;
        }
    }

    void drawBalls(std::vector<std::vector<RigidCircle *>> &balls,
                   const float &dt)
    {
        for (int i = 0; i < balls.size(); i++) {
            for (int j = 0; j < balls[i].size(); j++) {
                balls[i][j]->pos += balls[i][j]->vel * dt;
            }
        }

        for (int i = 0; i < balls.size(); i++) {
            for (int j = 0; j < balls[i].size(); j++) {
                balls[i][j]->draw();
            }
        }
    }

    void drawLines(std::vector<std::vector<RigidCircle *>> &balls)
    {
        for (int i = 0; i < balls.size(); i++) {
            for (int j = 0; j < balls[i].size(); j++) {
                auto cur = balls[i][j];

                // 가로
                if (j - 1 >= 0)
                    drawLine(Colors::green, cur->pos, Colors::green,
                             balls[i][j - 1]->pos);
                if (j + 1 < balls[i].size())
                    drawLine(Colors::green, cur->pos, Colors::green,
                             balls[i][j + 1]->pos);

                // 세로
                if (i - 1 >= 0)
                    drawLine(Colors::green, cur->pos, Colors::green,
                             balls[i - 1][j]->pos);
                if (i + 1 < balls.size())
                    drawLine(Colors::green, cur->pos, Colors::green,
                             balls[i + 1][j]->pos);

                // 대각
                if (i - 1 >= 0 && j + 1 < balls[i].size())
                    drawLine(Colors::green, cur->pos, Colors::green,
                             balls[i - 1][j + 1]->pos);
                if (i - 1 >= 0 && j - 1 >= 0)
                    drawLine(Colors::green, cur->pos, Colors::green,
                             balls[i - 1][j - 1]->pos);
                if (i + 1 < balls.size() && j + 1 < balls[i].size())
                    drawLine(Colors::green, cur->pos, Colors::green,
                             balls[i + 1][j + 1]->pos);
                if (i + 1 < balls.size() && j - 1 >= 0)
                    drawLine(Colors::green, cur->pos, Colors::green,
                             balls[i + 1][j - 1]->pos);
            }
        }
    }

    vec2 getForce(RigidCircle &cur, RigidCircle &other, const float &dt)
    {
        // coefficients
        const float l0 = 0.5f;
        const float coeff_k = 500.0f; // 용수철의 힘
        const float coeff_d = 5.0f; // 댐퍼의 힘

        // 스프링이 공에 가하는 힘은 원래 길이와 현재 길이에 비례함(other ->
        // target 방향) 댐퍼가 공에 가하는 힘은 두 공의 속도 차이에 비례함(other
        // -> target 방향)
        const auto distance = (cur.pos - other.pos).getMagnitude();
        const auto direction = (cur.pos - other.pos) / distance;

        const auto spring_force = direction * -(distance - l0) * coeff_k;
        const auto damping_force =
            direction * -((cur.vel - other.vel).getDotProduct(direction)) *
            coeff_d;

        const auto retForce = spring_force + damping_force;

        // cur가 받는 힘은 other도 받게 됨
        if (other.color.x == stickColor.x &&
            other.color.y == stickColor.y &&
            other.color.z == stickColor.z)
        {
            return retForce;
        }
        else
        {
            other.vel += -retForce / other.mass * dt;
            return retForce;
        }
    }

    void updateBalls(std::vector<std::vector<RigidCircle *>> &balls,
                     const float &dt)
    {
        const vec2 gravity(0.0f, -9.8f);

        for (int i = 0; i < balls.size(); i++) {
            for (int j = 0; j < balls[i].size(); j++) {
                if ((i == 0 && j == 0) || (i == 0 && j == 3))
                    continue;

                auto cur = balls[i][j];
                vec2 force(0.0f, 0.0f);
                int cnt = 0;

                // 가로
                if (j - 1 >= 0) {
                    force += getForce(*cur, *balls[i][j - 1], dt);
                    cnt++;
                }
                if (j + 1 < balls[i].size()) {
                    force += getForce(*cur, *balls[i][j + 1], dt);
                    cnt++;
                }
                // 세로
                if (i - 1 >= 0) {
                    force += getForce(*cur, *balls[i - 1][j], dt);
                    cnt++;
                }
                // 대각
                if (i - 1 >= 0 && j + 1 < balls[i].size()) {
                    force += getForce(*cur, *balls[i - 1][j + 1], dt);
                    cnt++;
                }
                if (i - 1 >= 0 && j - 1 >= 0) {
                    force += getForce(*cur, *balls[i - 1][j - 1], dt);
                    cnt++;
                }

                auto accel = gravity + force / cur->mass;
                cur->vel += accel * dt;
            }
        }
    }

public:
    std::vector<std::vector<RigidCircle *>> balls;

    RigidCircle stick0{vec2(-0.6f, 0.5f), vec2(0.0f, 0.0f), stickColor,
                       circleRadius, circleMass};
    RigidCircle stick1{vec2(0.6f, 0.5f), vec2(0.0f, 0.0f), stickColor,
                       circleRadius, circleMass};

    Example() : Game2D()
    {
        initBalls(balls);
        reset();
    }

    void reset()
    {
        clearBalls(balls);
        createBalls(balls);
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

        updateBalls(balls, dt);

        // draw
        drawWall();

        drawLines(balls);
        drawBalls(balls, dt);

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
