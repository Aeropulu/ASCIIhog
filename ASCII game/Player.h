#pragma once
#include "Entity.h"
#include "InputScheme.h"
#include "Sprite.h"
#include "Wall.h"

class Player :
    public Entity
{
    public: 
        Player(ConsoleBuffer, Sprite, float, float);
        void ProcessInput();
        void Jump();
        int state;
        float speedX, speedY;
        float nextX, nextY;
        void ProcessNextPos();
        void ProcessCollision(Wall);
        void Update();
        

    private:
        InputScheme* input;
};

