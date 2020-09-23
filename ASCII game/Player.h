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
        bool onGround;
        float speedX, speedY;
        float nextX, nextY;
        void ProcessNextPos();
        void ProcessCollision(Wall&);
        SMALL_RECT GetRectNextX();
        SMALL_RECT GetRectNextY();
        void Update();

        

    private:
        InputScheme* input;
};

