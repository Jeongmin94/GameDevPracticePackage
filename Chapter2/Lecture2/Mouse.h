#pragma once

#include "Game2D.h"

namespace jm {
class Mouse : public Game2D {
private:
    GeometricObject *go = nullptr;

public:
    void update() override
    {
        vec2 cursor = getCursorPos(true);

        if (isMouseButtonPressedAndReleased(GLFW_MOUSE_BUTTON_LEFT)) {
            if (go != nullptr) {
                delete go;
            }
            go = new Triangle(Colors::blue, cursor, 0.3f);
        }

        if (isMouseButtonPressedAndReleased(GLFW_MOUSE_BUTTON_RIGHT)) {
            if (go != nullptr) {
                delete go;
            }
            go = new Circle(Colors::red, cursor, 0.3f);
        }

        if (go != nullptr) {
            go->draw();
        }
    }
};
}; // namespace jm
