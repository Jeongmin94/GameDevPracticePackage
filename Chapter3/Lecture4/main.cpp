#include "Examples/PrimitivesGallery.h"
#include "Game2D.h"
#include "RandomNumberGenerator.h"
#include "RigidCircle.h"
#include <memory>
#include <vector>

namespace jm {
using namespace std;

static const auto gravity = vec2(0.0f, -9.8f);

class Particle {
public:
    vec2 pos;
    vec2 vel;
    RGB color;

    float rot;
    float angularVel;

    float age;
    float life;

    Particle() {}

    Particle(const vec2 &_pos, const vec2 &_vel, const RGB &_color,
             const float &_rot, const float &_angularVel, const float &_age,
             const float &_life)
        : pos(_pos), vel(_vel), color(_color), rot(_rot),
          angularVel(_angularVel), age(_age), life(_life)
    {
    }

    void update(const float &dt)
    {
        const auto acc = gravity; // assumes GA only.

        vel += acc * dt;
        pos += vel * dt;

        rot += angularVel * dt;

        // update age.
        age += dt;
    }
};

class ParticleSystem {
public:
    vector<Particle> particles;
    vector<Particle> show;
    bool isDrawing = false;

    RandomNumberGenerator rn;

    ParticleSystem() { reset(); }

    auto getRandomUnitVector()
    {
        const float theta = rn.getFloat(0.0f, 3.141592f * 2.0f); // 0.0 ~ 2pi

        return vec2{cos(theta), -sin(theta)};
    }

    auto getRandomColor()
    {
        return RGB{rn.getFloat(0.0f, 1.0f), rn.getFloat(0.0f, 1.0f),
                   rn.getFloat(0.0f, 1.0f)};
    }

    auto getRandomParticle(const vec2 &pos)
    {
        Particle new_particle;
        new_particle.pos = pos;
        new_particle.vel = getRandomUnitVector() * rn.getFloat(0.01f, 2.0f);
        new_particle.color = getRandomColor();
        new_particle.age = 0;
        new_particle.life = rn.getFloat(0.1f, 1.0f);
        new_particle.rot = rn.getFloat(0.0f, 360.0f);
        new_particle.angularVel = rn.getFloat(-1.0f, 1.0f) * 360.0f * 4.0f;

        return new_particle;
    }

    void reset()
    {
        particles.clear();

        for (int i = 0; i < 1000; i++) {
            Particle new_particle;
            new_particle.pos =
                vec2(0.0f, 0.5f) +
                vec2(rn.getFloat(0.0f, 0.01f), rn.getFloat(0.0f, 0.01f));
            new_particle.vel = getRandomUnitVector() * rn.getFloat(0.01f, 2.0f);
            new_particle.color = getRandomColor();
            new_particle.age = 0;
            new_particle.life = rn.getFloat(0.1f, 1.0f);
            new_particle.rot = rn.getFloat(0.0f, 360.0f);
            new_particle.angularVel = rn.getFloat(-1.0f, 1.0f) * 360.0f * 4.0f;

            show.push_back(new_particle);
        }
    }

    void createParticles(const vec2 &cursor)
    {
        // initialize particles
        for (int i = 0; i < 1000; ++i) {
            particles.push_back(getRandomParticle(cursor));
        }
    }

    void infinite(const vec2 &cursor, const float &dt)
    {
        for (auto &pt : show) {
            pt.update(dt);
        }

        for (auto &p : show) {
            if (p.age > p.life) {
                p.pos = vec2(0.0f, 0.5f) + vec2(rn.getFloat(0.0f, 0.01f),
                                                rn.getFloat(0.0f, 0.01f));
                p.vel = getRandomUnitVector() * rn.getFloat(0.01f, 2.0f);
                p.color = getRandomColor();
                p.age = 0;
                p.life = rn.getFloat(0.1f, 1.0f);
                p.rot = rn.getFloat(0.0f, 360.0f);
                p.angularVel = rn.getFloat(-1.0f, 1.0f) * 360.0f * 4.0f;
                continue;
            }
            // update color (blend with background color)
            // alpha blended
            const float alpha = 1.0f - p.age / p.life;
            const RGB blendedColor = {p.color.r * alpha + 1.0f * (1.0f - alpha),
                                      p.color.g * alpha + 1.0f * (1.0f - alpha),
                                      p.color.b * alpha +
                                          1.0f * (1.0f - alpha)};

            // rotate
            beginTransformation();
            translate(p.pos);
            rotate(p.rot);
            drawFilledStar(blendedColor, 0.03f, 0.01f);
            endTransformation();
        }
    }

    void update(const float &dt)
    {
        for (auto &pt : particles) {
            pt.update(dt);
            // remove particles when they are 1. too old, 2. out of screen.
        }
    }

    void draw(const vec2 &cursor, vector<Particle> &p)
    {
        if (p.empty())
            createParticles(cursor);

        beginTransformation();

        bool checkOldParticles = false;
        for (const auto &pt : p) {
            if (pt.age > pt.life) {
                continue;
            }
            if (checkOldParticles == false)
                checkOldParticles = true;

            // update color (blend with background color)
            // alpha blended
            const float alpha = 1.0f - pt.age / pt.life;
            const RGB blendedColor = {
                pt.color.r * alpha + 1.0f * (1.0f - alpha),
                pt.color.g * alpha + 1.0f * (1.0f - alpha),
                pt.color.b * alpha + 1.0f * (1.0f - alpha)};

            // rotate
            beginTransformation();
            translate(pt.pos);
            rotate(pt.rot);
            drawFilledStar(blendedColor, 0.03f, 0.01f);
            endTransformation();
        }

        if (!checkOldParticles) {
            isDrawing = false;
            for (auto &pt : p) {
                pt.pos = cursor;
                pt.vel = getRandomUnitVector() * rn.getFloat(0.01f, 2.0f);
                pt.color = getRandomColor();
                pt.age = 0;
                pt.life = rn.getFloat(0.1f, 1.0f);
                pt.rot = rn.getFloat(0.0f, 360.0f);
                pt.angularVel = rn.getFloat(-1.0f, 1.0f) * 360.0f * 4.0f;
            }
        }

        endTransformation();
    }
};

class Example : public Game2D {
public:
    ParticleSystem ps;

    Example() : Game2D() { reset(); }

    void reset() { ps.reset(); }

    // TODO1: 마우스 클릭하는 곳에서 파티클 효과 발생
    // TODO2: 파티클 분수대
    void update() override
    {
        const float dt = getTimeStep() * 0.4f;
        auto cursor = getCursorPos(true);

        if (isMouseButtonPressedAndReleased(GLFW_MOUSE_BUTTON_LEFT)) {
            if (ps.isDrawing) {
                ps.particles.clear();
            }
            ps.isDrawing = true;
        }

        if (ps.isDrawing) {
            ps.update(dt);
            ps.draw(cursor, ps.particles);
        }

        ps.infinite(cursor, dt);

        // reset button
        if (isKeyPressedAndReleased(GLFW_KEY_R))
            reset();
    }
};
} // namespace jm

int main(void)
{
    jm::Example().run();

    return 0;
}
