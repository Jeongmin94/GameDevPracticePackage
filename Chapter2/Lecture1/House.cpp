#include "House.h"


void jm::House::draw(const float &time)
{
    // draw a house
    beginTransformation();
    {
        translate(pos);
        rotate(getRadian(time * 360.0f * rotateSpeed));

        // wall
        drawFilledBox(color.ofWall(), 0.2f, 0.2f);

        // roof
        drawFilledTriangle(color.ofRoof(), {-0.13f, 0.1f}, {0.13f, 0.1f},
                           {0.0f, 0.2f});
        drawWiredTriangle(color.ofRoof(), {-0.13f, 0.1f}, {0.13f, 0.1f},
                          {0.0f, 0.2f});

        window->draw(time);
    }
    endTransformation();
}
