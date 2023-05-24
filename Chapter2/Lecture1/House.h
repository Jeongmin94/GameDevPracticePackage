#pragma once

#include "Game2D.h"

namespace jm {
class HouseColor {
private:
    const RGB roof = Colors::red;
    const RGB wall = Colors::gold;
    const RGB window = Colors::green;

public:
    HouseColor() {}

    HouseColor(const RGB &roof, const RGB &wall, const RGB &window)
        : roof(roof), wall(wall), window(window)
    {
    }

    const RGB &ofRoof() { return roof; }
    const RGB &ofWall() { return wall; }
    const RGB &ofWindow() { return window; }
};

class Window {
public:
    const RGB &window = Colors::green;
    float rotateSpeed = 1.0f;

    virtual void draw(const float &time)
    {
        std::cout << "window" << std::endl;

        // window
        rotate(getRadian(time * 360.0f * rotateSpeed * 2.0f));
        drawFilledBox(window, 0.1f, 0.1f);
        drawWiredBox(Colors::gray, 0.1f, 0.1f);
        drawLine(Colors::gray, {0.0f, -0.05f}, Colors::gray, {0.0f, 0.05f});
        drawLine(Colors::gray, {-0.05f, 0.0f}, Colors::gray, {0.05f, 0.0f});
    }
};

class CircleWindow : public Window {
private:
    int CIRCLE = -1;

public:
    virtual void draw(const float &time)
    {
        std::cout << "circle" << std::endl;
        // window
        drawFilledCircle(window, 0.10f);
        drawLine(Colors::gray, {0.0f, -0.05f}, Colors::gray, {0.0f, 0.05f});
        drawLine(Colors::gray, {-0.05f, 0.0f}, Colors::gray, {0.05f, 0.0f});
    }
};

class House {
private:
    HouseColor color;
    vec2 pos = vec2(0.0f, 0.0f);
    float rotateSpeed = 10.0f;

    Window *window = new Window();

public:
    House() {}

    House(const HouseColor &color, const vec2 &pos) : color(color), pos(pos) {}

    void setPos(const vec2 &_pos) { pos = _pos; }
    void setRotateSpeed(const float &_rotateSpeed)
    {
        rotateSpeed = _rotateSpeed;
        window->rotateSpeed = _rotateSpeed;
    }

    void setWindow()
    { delete window;
        window = new CircleWindow();
    }

    void draw(const float &time = 0.0f);

    ~House()
    { delete window;
    }
};
} // namespace jm
