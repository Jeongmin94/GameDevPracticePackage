#pragma once

#include "Game2D.h"
#include <vector>

namespace jm {
class TE {
public:
    vec2 center = vec2(0.0f, 0.0f);

    bool isValidX(const float &x, const float &ratio)
    {
        return (x > -ratio && x < ratio);
    }

    bool isValidY(const float &y) { return (y > -1.0f && y < 1.0f); }

    void moveHorizontal(const float &dx, TE &te, const float &ratio)
    {
        float next_x = te.center.x + dx;
        if (isValidX(next_x, ratio)) {
            te.center.x = next_x;
        }
    }

    void moveVertical(const float &dy, TE &te)
    {
        float next_y = te.center.y + dy;
        if (isValidY(next_y)) {
            te.center.y = next_y;
        }
    }
};

class MyTank : public TE {
public:
    // vec2 direction = vec2(1.0f, 0.0f, 0.0f);

    void draw()
    {
        beginTransformation();
        {
            translate(center);

            drawFilledBox(Colors::green, 0.25f, 0.1f); // body

            translate(-0.02f, 0.1f);
            drawFilledBox(Colors::blue, 0.15f, 0.09f); // turret

            translate(0.15f, 0.0f);
            drawFilledBox(Colors::red, 0.15f, 0.03f); // barrel
        }
        endTransformation();
    }
};

class MyBullet : public TE {
private:
    vec2 velocity = vec2(0.0f, 0.0f);
    constexpr static float normalize_x = 0.2f;
    constexpr static float normalize_y = 0.1f;

public:
    MyBullet(const MyTank &tank, const vec2 &vec)
    {
        this->center = tank.center;
        this->center.x += normalize_x;
        this->center.y += normalize_y;
        this->velocity = vec;
    }

    void draw()
    {
        beginTransformation();
        translate(center);
        drawFilledRegularConvexPolygon(Colors::yellow, 0.02f, 8);
        drawWiredRegularConvexPolygon(Colors::gray, 0.02f, 8);
        endTransformation();
    }

    void update(const float &dt) { center += velocity * dt; }

    ~MyBullet() { std::cout << "bullet destroyed" << std::endl; }
};

class TankExample : public Game2D {

private:
    const static int TANK_WIDTH = 1024;
    const static int TANK_HEIGHT = 768;
    constexpr static float TANK_RATIO = 1024.0f / 768.0f;

    vec2 bullet_speed = vec2(2.0f, 0.0f);
    int fire_count = 5;
    int bullet_count = 0;
    int bullet_idx = 0;

public:
    MyTank tank;

    // MyBullet *bullet = nullptr;
    std::vector<MyBullet *> bullets;

public:
    TankExample()
        : Game2D("This is my digital canvas!", TANK_WIDTH, TANK_HEIGHT, false,
                 2)
    {
        bullets.resize(fire_count);
    }

    ~TankExample() {}

    void update() override
    {
        // move tank
        if (isKeyPressed(GLFW_KEY_LEFT))
            tank.moveHorizontal(-0.5f * getTimeStep(), tank, TANK_RATIO);
        if (isKeyPressed(GLFW_KEY_RIGHT))
            tank.moveHorizontal(0.5f * getTimeStep(), tank, TANK_RATIO);
        if (isKeyPressed(GLFW_KEY_DOWN))
            tank.moveVertical(-0.5f * getTimeStep(), tank);
        if (isKeyPressed(GLFW_KEY_UP))
            tank.moveVertical(0.5f * getTimeStep(), tank);

        // shoot a cannon ball
        if (isKeyPressedAndReleased(GLFW_KEY_SPACE)) {
            if (bullet_count < fire_count) {
                bullets[bullet_idx++ % fire_count] =
                    new MyBullet(tank, bullet_speed);
                bullet_count++;
            }
        }

        for (auto bullet : bullets) {
            if (bullet != nullptr) {
                bullet->update(getTimeStep());
            }
        }

        // rendering
        tank.draw();

        for (int i = 0; i < fire_count; i++) {
            MyBullet *b = bullets[i];
            if (b != nullptr) {
                if (b->isValidX(b->center.x, TANK_RATIO)) {
                    b->draw();
                }
                else {
                    delete b;
                    bullets[i] = nullptr;
                    bullet_count--;
                }
            }
        }
    }
};
} // namespace jm
