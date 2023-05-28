#include "Game2D.h"
#include "Examples/PrimitivesGallery.h"
#include "Examples/TankExample.h"
#include "RandomNumberGenerator.h"
#include <vector>
#include <memory>
#include <fstream>

namespace jm
{

}

int main(void)
{
    std::ifstream is("key_binding.txt");
    jm::TankExample te;

	is >> te;
    te.run();
	//jm::Game2D().init("This is my digital canvas!", 1280, 960, false).run();
	//jm::PrimitivesGallery().run();

	return 0;
}
