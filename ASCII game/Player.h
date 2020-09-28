#pragma once
#include "Entity.h"
#include "InputScheme.h"
#include "Sprite.h"
#include "Wall.h"

class Player :
    public Entity
{
    public: 
        Player(ConsoleBuffer, Sprite**, float, float, InputScheme *input = nullptr);
        void ProcessInput();
        void Jump();
        void Die();
        float timer;
        bool onGround = false;
        float speedX, speedY;
        float nextX, nextY;
        void ProcessNextPos();
        void ProcessCollision(Wall&);
        void ProcessState();
        void SetState(int);
        bool SendState(int state);
        SMALL_RECT GetRectNextX();
        SMALL_RECT GetRectNextY();
        void UpdatePos();
        unsigned long GetElapsedMs();
        LONGLONG freq;
        LARGE_INTEGER lastUpdateTime;
        

    private:
        InputScheme* input;
};

