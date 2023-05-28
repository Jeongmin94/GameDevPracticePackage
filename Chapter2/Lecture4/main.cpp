#include "Box.h"
#include "Circle.h"
#include "Examples/PrimitivesGallery.h"
#include "Game2D.h"
#include "RandomNumberGenerator.h"
#include "Triangle.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace jm {
class Example : public Game2D {
public:
    std::vector<std::unique_ptr<GeometricObject>> my_objs;

    Example(const std::string &name, const float &x, const float &y,
            const float &size)
        : Game2D()
    {
        addGeometricObject(name, x, y, size);
    }

    Example() {}

    ~Example()
    {
        // delete is unnecessary with shared_ptr
        // for (const auto & obj : my_objs)
        //	delete obj;
    }

    void addGeometricObject(const std::string &name, const float &x,
                            const float &y, const float &size)
    {
        vec2 pos{x, y};
        if (name._Equal("Circle")) {
            my_objs.push_back(
                std::make_unique<Circle>(Circle{Colors::blue, pos, size}));
        }

        if (name._Equal("Triangle")) {
            my_objs.push_back(
                std::make_unique<Triangle>(Triangle{Colors::red, pos, size}));
        }
    }

    void update() override
    {
        for (const auto &obj : my_objs) {
            obj->draw();
        }
    }

    friend std::istream &operator>>(std::istream &in, Example &example)
    {
        std::string name;
        float x, y, size;

        in >> name >> x >> y >> size;

        example.addGeometricObject(name, x, y, size);

        return in;
    }
};
} // namespace jm

int main(void)
{
    using namespace std;
    using namespace jm;

    // jm::Example().run();
    //  jm::Game2D().init("This is my digital canvas!", 1280, 960, false).run();
    //  jm::PrimitivesGallery().run();
    // std::cout << "그리고 싶은 물체와 좌표, 사이즈를 입력해주세요: ";
    // std::cin >> name >> x >> y >> size;

    // Circle 0.1 0.2 0.3
    // Triangle 0.1 0.2 0.3
    // jm::Example(name, x, y, size).run();

    const string fileName = "script.txt";
    ifstream is(fileName);

    Example exam;

    while (!is.eof())
        is >> exam;

    exam.run();
}
