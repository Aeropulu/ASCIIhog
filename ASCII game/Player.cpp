#include "Player.h"
#include <Windows.h>
#include "KeyboardScheme.h"
#include "Wall.h"

Player::Player(ConsoleBuffer b, Sprite s, float posX, float posY) : Entity(b, s, posX, posY)
{
    this->input = new KeyboardScheme();
    state = 0;
    speedX = 0;
    speedY = 0;
    nextX = x;
    nextY = y;
}

void Player::ProcessInput()
{
    short state = input->GetState();
    if (state & 1)
    {
        Jump();
    }
    if (state & 2)
    {
        speedY += 0.01;
    }
    if (state & 4)
    {
        speedX -= 0.01;
    }
    if (state & 8)
    {
        speedX += 0.01;
    }
}

void Player::ProcessNextPos()
{
    speedX *= 0.96;
    speedY *= 0.96;

    nextX = x + speedX;
    nextY = y + speedY;
}

void Player::ProcessCollision(Wall w) 
{
    if (Overlap(w))
    {
        speedX = 0;
        speedY = 0;
        nextX = x;
        nextY = y;
    }
}

void Player::Update()
{
    x = nextX;
    y = nextY;
}

void Player::Jump()
{
    this->speedY = -0.5;
}
