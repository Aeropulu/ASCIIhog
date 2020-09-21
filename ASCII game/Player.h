#pragma once
#include "Entity.h"
class Player :
    public Entity
{
    public: 
        Player(ConsoleBuffer, float, float);
        void Draw();
};

