#pragma once

#include "Game2D.h"

namespace jm {

class Bullet {
private:
    vec2 center = vec2(0.45f, 0.0f);
    vec2 velocity = vec2(2.0f, 2.0f);
    const float bullet_degree;

    bool isValidX(const float &x, const float &ratio)
    {
        return (x > -ratio && x < ratio);
    }

    bool isValidY(const float &y) { return (y > -1.0f && y < 1.0f); }

public:
    Bullet(const float &degree) : bullet_degree(degree) {}
    ~Bullet() { std::cout << "destory bullet" << std::endl; }

    void drawBullet(const vec2 &gun_pos)
    {
        beginTransformation();
        {
            rotate(bullet_degree);
            translate(center);
            drawFilledRegularConvexPolygon(Colors::red, 0.02f, 8);
            drawWiredRegularConvexPolygon(Colors::gray, 0.02f, 8);
        }
        endTransformation();
    }

    void update(const float &dt)
    {
        center = vec2(center.x + (dt * velocity.x), 0.0f);
        std::cout << center.x << ' ' << center.y << std::endl;
    }

    bool isValid(const float &ratio)
    {
        return isValidX(center.x, ratio) && isValidY(center.y);
    }

    float getX() { return center.x; }
    float getY() { return center.y; }
};

class Follow : public Game2D {
private:
    const float ratio = 1.33333;
    const vec2 gun_pos = vec2(0.3f, 0.0f);
    Bullet *bullet = nullptr;

    float getDegree(const float &radian) { return 180 / 3.141592f * radian; }

    void drawCenter() { drawFilledCircle(Colors::yellow, 0.2f); }

    void drawGun() { drawFilledBox(Colors::black, 0.3f, 0.075f); }

    void drawTurret(const float &degree)
    {
        beginTransformation();
        rotate(degree);

        drawCenter();
        translate(gun_pos);
        drawGun();
        endTransformation();
    }

public:
    void update() override
    {
        vec2 cursor = getCursorPos(true);
        float degree = getDegree(atan2(cursor.y, cursor.x));

        if (isMouseButtonPressedAndReleased(GLFW_MOUSE_BUTTON_LEFT)) {
            if (bullet == nullptr) {
                bullet = new Bullet(degree);
            }
        }

        if (bullet != nullptr) {
            bullet->update(getTimeStep());
        }

        drawTurret(degree);

        if (bullet != nullptr) {
            if (bullet->isValid(ratio)) {
                bullet->drawBullet(gun_pos);
            }
            else {
                delete bullet;
                bullet = nullptr;
            }
        }
    }
};
} // namespace jm
