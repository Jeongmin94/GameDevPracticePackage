#include "FaceExample.h"
#include "Game2D.h"
#include "MyFaceExample.h"
#include "PrimitivesGallery.h"
#include "RotatingStarExample.h"
#include "SolarSystem.h"
#include "TankExample.h"
#include "TransformationExample.h"
#include "WalkingPerson.h"
#include "CursorStar.h"
#include "BlueCircle.h"
#include "Follow.h"
#include "fmod.hpp"
#include <conio.h>

namespace jm {

} // namespace jm

int main(void)
{
    FMOD::System *system(nullptr);
    FMOD::Sound *sound(nullptr);
    FMOD::Channel *channel(nullptr);
    FMOD_RESULT result;
    void *extradriverdata(nullptr);
    result = FMOD::System_Create(&system);
    if (result != FMOD_OK)
        return -1;

    result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
    if (result != FMOD_OK)
        return -1;

    FMOD::Channel *c(nullptr);
    FMOD::Sound *t(nullptr);
    system->createSound("swish.wav", FMOD_LOOP_OFF, 0, &t);
    result = system->createSound("drumloop.wav", FMOD_LOOP_NORMAL, 0, &sound);
    if (result != FMOD_OK)
        return -1;

    result = system->playSound(sound, 0, false, &channel);
    if (result != FMOD_OK)
        return -1;


    while (true)
    {
        result = system->update();
        if (result != FMOD_OK)
            return -1;

        std::cout << "Press 0 to pause, 1 to resume, and x to exit"
                  << std::endl;

        int i = getch();

        if (channel)
        {
            bool playing = false;
            result = channel->isPlaying(&playing);
            if (!playing)
                break;
        }

        if (i == '0')
        {
            channel->setPaused(true);
        }
        else if (i == '1')
        {
            channel->setPaused(false);
        }
        else if (i == 'x')
        {
            break;
        }
        else if (i == 'z')
        {
            system->playSound(t, 0, false, &c);
        }
    }


    return 0;
}
