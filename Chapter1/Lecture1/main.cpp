#include "FaceExample.h"
#include "Game2D.h"
#include "PrimitivesGallery.h"
#include "RotatingStarExample.h"
#include "SolarSystem.h"
#include "TankExample.h"
#include "WalkingPerson.h"
#include "TransformationExample.h"

namespace jm {

} // namespace jm

int main(void)
{
    // jm::MouseExample().init("This is my digital canvas!", 1000, 1000,
    // false).run(); jm::Game2D().init("This is my digital canvas!", 1280, 960,
    // false).run();
    // jm::PrimitivesGallery().init("Primitive Gallery", 1280, 960,
    // false).run(); jm::SolarSystem().run(); jm::FaceExample().run();
    // jm::WalkingPerson().run();
    // jm::TankExample().run();

    // lec1.1 rotating star
    // jm::RotatingStarExample().run();

    // lec1.2 transformation example
    // jm::TransformationExample().run();

    // lec1.2 solar system
    jm::SolarSystem().run();

    return 0;
}
