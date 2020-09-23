#pragma once
#include "Entity.h"
class Wall :
    public Entity
{
    public:
        Wall(ConsoleBuffer, int, int, int, int);
        Sprite** GenerateSprite(int, int);
};

