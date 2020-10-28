#pragma once
#include "Entity.h"
class Wall :
    public Entity
{
    public:
        Wall(ConsoleBuffer, float, float, int, int);
        Sprite** GenerateSprite(int, int);
        ~Wall();
        
};

