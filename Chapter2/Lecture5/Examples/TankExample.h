#pragma once

#include "Game2D.h"
#include <iostream>
#include <map>
#include <memory>

namespace jm {
class Actor {
public:
    virtual void moveUp(float dt) = 0;
    virtual void moveDown(float dt) = 0;
    virtual void moveLeft(float dt) = 0;
    virtual void moveRight(float dt) = 0;

    virtual void fire(float dt) = 0;
};

class Command {
public:
    virtual ~Command() {}
    virtual void execute(Actor &actor, float dt) = 0;
};

class UpCommand : public Command {
public:
    virtual void execute(Actor &actor, float dt) override { actor.moveUp(dt); }
};

class DownCommand : public Command {
public:
    virtual void execute(Actor &actor, float dt) override
    {
        actor.moveDown(dt);
    }
};
class LeftCommand : public Command {
public:
    virtual void execute(Actor &actor, float dt) override
    {
        actor.moveLeft(dt);
    }
};
class RightCommand : public Command {
public:
    virtual void execute(Actor &actor, float dt) override
    {
        actor.moveRight(dt);
    }
};
class FireCommand : public Command {
public:
    virtual void execute(Actor &actor, float dt) override
    {
        actor.fire(dt);
    }
};

class MyTank : public Actor {
public:
    vec2 center = vec2(0.0f, 0.0f);
    // vec2 direction = vec2(1.0f, 0.0f, 0.0f);

    void moveUp(float dt) override { center.y += 0.5f * dt; }
    void moveDown(float dt) override { center.y -= 0.5f * dt; }
    void moveLeft(float dt) override { center.x -= 0.5f * dt; }
    void moveRight(float dt) override { center.x += 0.5f * dt; }
    void fire(float dt) override { std::cout << "SHOOT!!!" << std::endl; }

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

class InputHandler {
public:
    std::map<int, std::unique_ptr<Command>> key_command_map;

    InputHandler() {}

    void setInputHandle(const std::string &key, const std::string &binding)
    {
        int k;
        if (key._Equal("SPACE")) {
            k = GLFW_KEY_SPACE;
        }
        if (key._Equal("W")) {
            k = GLFW_KEY_W;
        }
        if (key._Equal("A")) {
            k = GLFW_KEY_A;
        }
        if (key._Equal("D")) {
            k = GLFW_KEY_D;
        }
        if (key._Equal("S")) {
            k = GLFW_KEY_S;
        }

        if (binding._Equal("shoot")) {
            key_command_map[k] = std::make_unique<FireCommand>();
        }
        if (binding._Equal("move_up")) {
            key_command_map[k] = std::make_unique<UpCommand>();
        }
        if (binding._Equal("move_down")) {
            key_command_map[k] = std::make_unique<DownCommand>();
        }
        if (binding._Equal("move_left")) {
            key_command_map[k] = std::make_unique<LeftCommand>();
        }
        if (binding._Equal("move_right")) {
            key_command_map[k] = std::make_unique<RightCommand>();
        }
    }

    void handleInput(Game2D &game, Actor &actor, float dt)
    {
        for (auto &m : key_command_map) {
            if (game.isKeyPressed(m.first))
                m.second->execute(actor, dt);
        }
    }
};

class TankExample : public Game2D {
public:
    MyTank tank;

    InputHandler input_handler;

    float speed = 2.0f;

public:
    TankExample() : Game2D("This is my digital canvas!", 1024, 768, false, 2)
    {
        // key mapping
        // input_handler.key_command_map[GLFW_KEY_UP] = new UpCommand;
    }

    ~TankExample() {}

    void update() override
    {
        input_handler.handleInput(*this, tank, getTimeStep());

        // rendering
        tank.draw();
    }

    friend std::istream &operator>>(std::istream &in, TankExample &te)
    {

        while (!in.eof()) {
            std::string key, binding;
            in >> key >> binding;
            te.input_handler.setInputHandle(key, binding);
        }

        return in;
    }
};
} // namespace jm