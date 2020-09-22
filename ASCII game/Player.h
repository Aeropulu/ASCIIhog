#pragma once
#include "Entity.h"
#include "InputScheme.h"
#include "Sprite.h"

class Player :
    public Entity
{
    public: 
        Player(ConsoleBuffer, Sprite, float, float);
        void ProcessInput();
        void Draw();
        int state;

    private:
        InputScheme* input;
};

