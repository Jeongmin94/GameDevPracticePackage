#include "MyFaceExample.h"

void jm::MyFaceExample::update()
{
    // face
    drawWiredCircle(Colors::black, face);
    drawFilledCircle(Colors::white, face);

    // eyes
    const vec2 left_eye_pos(-0.3f, 0.2f);
    const vec2 right_eye_pos(0.3f, 0.2f);
    beginTransformation();
    {
        translate(left_eye_pos);
        rotate(time * -90.0f);
        drawFilledStar(Colors::gold, eyes_outer_radian, eyes_inner_radian);
    }
    endTransformation();

    beginTransformation();
    {
        translate(right_eye_pos);
        rotate(time * 90.0f);
        drawFilledStar(Colors::gold, eyes_outer_radian, eyes_inner_radian);
    }
    endTransformation();

    // mouth
    const vec2 mouth_pos(0.0f, -0.5f);
    beginTransformation();
    {
        translate(mouth_pos);
        scale(1.0f, 0.2f);
        drawFilledCircle(Colors::red, 0.4f);
    }
    endTransformation();

    // nose
    const vec2 p1(0.0f, 0.3f);
    const vec2 p2(-0.04f, -0.2f);
    const vec2 p3(0.04f, -0.2f);
    beginTransformation();
    {
        drawLine(Colors::blue, p1, Colors::black, p2);
        drawLine(Colors::blue, p1, Colors::black, p3);
        drawLine(Colors::black, p2, Colors::black, p3);
    }
    endTransformation();

    time += getTimeStep();
}
