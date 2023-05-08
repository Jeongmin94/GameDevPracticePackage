#pragma once

#include "Game2D.h"
#include <vector>

namespace jm {
/*
TODO:
- [x] add left arm and left leg
- [x] make a Person class and use it to draw many people.
- [x] make an Ironman and allow for him to shoot repulsor beam with his right
hand
*/

class Person {
private:
    float person_time = 0.0f;
    void drawFace()
    {
        // gold face
        beginTransformation();
        translate(0.0f, 0.12f);
        drawFilledCircle(Colors::gold, 0.08f);
        translate(0.05f, 0.03f);
        drawFilledCircle(Colors::white, 0.01f); // while eye
        endTransformation();
    }

    void drawArm(const float &degree, const RGB &color)
    {
        beginTransformation();
        {
            rotate(degree); // animation!
            scale(1.0f, 2.0f);
            translate(0.0f, -0.1f);
            drawFilledBox(color, 0.05f, 0.18f);
            endTransformation();
        }
    }

    void drawLeg(const float &degree, const RGB &color)
    {
        beginTransformation();
        {
            translate(0.0f, -0.6f);
            translate(0.0f, 0.2f);
            rotate(degree); // animation!
            translate(0.0f, -0.2f);
            drawFilledBox(color, 0.1f, 0.4f);
        }
        endTransformation();
    }

    void drawBody()
    {
        // red body
        beginTransformation();
        scale(1.0f, 2.0f);
        translate(0.0f, -0.1f);
        drawFilledBox(Colors::red, 0.13f, 0.2f);
        endTransformation();
    }

public:
    void draw(float &time)
    {
        drawFace();

        // blue left arm
        drawArm(-sin(time * 5.0f) * 30.0f, Colors::blue);

        // green left leg
        drawLeg(-sinf(time * 5.0f + 3.141592f) * 30.0f, Colors::green);

        drawBody();

        // green right arm
        drawArm(sin(time * 5.0f) * 30.0f, Colors::green);

        // blue right leg
        drawLeg(sinf(time * 5.0f + 3.141592f) * 30.0f, Colors::blue);
    }

    void stop(float &time)
    {
        drawFace();

        // blue left arm
        drawArm(10.0f, Colors::blue);

        // green left leg
        drawLeg(0.0f, Colors::green);

        drawBody();

        // green right arm
        drawArm(90.0f, Colors::green);

        // blue right leg
        drawLeg(0.0f, Colors::blue);
    }

    void shoot(float &dt)
    {
        if (person_time > 2.6f) {
            person_time = 2.6f;
        }
        const vec2 center(0.4f, 0.0f);
        const vec2 shoot_start(0.0f, 0.0f);
        const vec2 shoot_end(person_time, 0.0f);

        setLineWidth(5.0f);
        translate(center);
        drawFilledCircle(Colors::red, 0.02f);

        drawLine(Colors::red, shoot_start, Colors::gray, shoot_end);

        person_time += dt;
    }

    void setPersonTimeZero() { person_time = 0.0f;
    }

    void shoot() {}

    ~Person() { std::cout << "delete person" << std::endl; }
};

class WalkingPerson : public Game2D {
    float time = 0.0f;
    std::vector<Person *> people;
    int max = 1;

public:
    WalkingPerson()
    {
        for (int i = 0; i < max; i++) {
            people.push_back(new Person());
        }
    }

    ~WalkingPerson()
    {
        for (auto p : people) {
            delete p;
        }
    }

    void stop(float &time)
    {
        for (int i = 0; i < max; i++) {
            beginTransformation();
            translate(vec2(-1.0f + i, 0.0f));
            people[i]->stop(time);
            endTransformation();
        }
    }

    void shoot(float& time) {
        for (int i = 0; i < max; i++) {
            beginTransformation();
            translate(vec2(-1.0f + i, 0.0f));
            people[i]->shoot(time);
            endTransformation();
        }
    }

    void drawWalking(float &time)
    {
        for (int i = 0; i < max; i++) {
            beginTransformation();
            translate(vec2(-1.0f + i, 0.0f));
            people[i]->draw(time);
            people[i]->setPersonTimeZero();
            endTransformation();
        }
    }

    void update() override
    {
        float dt = this->getTimeStep();
        if (isKeyPressed(GLFW_KEY_SPACE)) {
            stop(time);
            shoot(dt);
        }
        else {
            drawWalking(time);
        }

        time += dt;
    }
};
} // namespace jm
