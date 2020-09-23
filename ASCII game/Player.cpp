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
        if (onGround)
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
    speedY += 0.01;
    speedX *= 0.96;
    speedY *= 0.96;

    nextX = x + speedX;
    nextY = y + speedY;
}

void Player::ProcessCollision(Wall &w) 
{
    if (Entity::Overlap(GetRectNextX(), w.GetRect()))
    {
        speedX = 0;
        nextX = x;
    }

    if (Entity::Overlap(GetRectNextY(), w.GetRect()))
    {
        speedY = 0;
        nextY = y;
        onGround = true;
    }
}


SMALL_RECT Player::GetRectNextX()
{
    return { (short)nextX, (short)y, (short)(sprite.w + nextX), (short)(sprite.h + y) };
}

SMALL_RECT Player::GetRectNextY()
{
    return { (short)x, (short)nextY, (short)(sprite.w + x), (short)(sprite.h + nextY) };
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
