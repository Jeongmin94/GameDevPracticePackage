#include "MyFaceExample.h"

void jm::MyFaceExample::update()
{
    drawWiredCircle(Colors::black, face);
    drawFilledCircle(Colors::white, face);
}
