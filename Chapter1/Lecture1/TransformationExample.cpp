#include "TransformationExample.h"

void jm::TransformationExample::rotateBox() {
    const vec2 center(-0.2f, 0.0f);

	rotate(time * 90.0f);
	translate(-center);
	rotate(time * 90.0f);
	scale(2.0f, 0.2f);
	drawPoint(Colors::black, center, 5.0f);
    drawWiredBox(Colors::red, 0.4f, 0.2f);

	time += getTimeStep();
}
