#include "TransformationExample.h"

void jm::TransformationExample::rotateBox() {
    const vec2 center(0.0f, 0.0f);

    beginTransformation();
    {
        rotate(time * 60.0f);
	    translate(0.5f, 0.0f);
        drawWiredBox(Colors::red, 1.0f, 0.2f);

        beginTransformation();
        {
            rotate(time*90.0f);
            drawWiredBox(Colors::blue, 0.5f, 0.2f);
        }
        endTransformation();
    }
    endTransformation();


	time += getTimeStep();
}
