#include <Windows.h>
#include "Player.h"
#include "KeyboardScheme.h"
#include "Wall.h"

Player::Player(ConsoleBuffer b, Sprite** s, float posX, float posY) : Entity(b, s, posX, posY)
{
    this->input = new KeyboardScheme();
    speedX = 0;
    speedY = 0;
    nextX = x;
    nextY = y;
    QueryPerformanceCounter(&lastUpdateTime);
    LARGE_INTEGER li_freq;
    QueryPerformanceFrequency(&li_freq);
    freq = li_freq.QuadPart;
    freq /= 1000;
}

void Player::ProcessState()
{
    switch(state)
    {
        case 0: // idle state
            break;
        case 1: // idle 2 : recovery time
            if (GetElapsedMs() >= 400)
                SetState(0);
            break;
        case 2: // falling
            break;
        case 3: // running frame 1
            if (GetElapsedMs() >= 300)
            {
                SetState(4);
            }
            break;
        case 4: // running frame 2
            if (GetElapsedMs() >= 300)
            {
                SetState(5);
            }
            break;
        case 5: // running frame 3
            if (GetElapsedMs() >= 300)
            {
                SetState(6);
            }
            break;
        case 6: // running frame 4
            if (GetElapsedMs() >= 300)
            {
                SetState(3);
            }
            break;
        case 7: // attack frame 1
            if (GetElapsedMs() >= 500)
                SetState(8);
            break;
        case 8: // attack frame 2
            if (GetElapsedMs() >= 300)
                SetState(0);
            break;
        case 9: // attack falling 
            break;
        case 10: // blocking
            if (GetElapsedMs() >= 700)
                SetState(0);
            break;
        case 11: // recovery ?
            break;
    }

}

void Player::SetState(int state)
{
    LARGE_INTEGER timeNow;
    QueryPerformanceCounter(&timeNow);
    lastUpdateTime = timeNow;
    this->state = state;
}

bool Player::SendState(int state)
{
    if (this->state != state)
    {
        if (state == 0)
        {
            SetState(0);
        }

        if (state == 2 && (this->state != 2) && (this->state <= 6) ) // try to jump
            if (onGround)
            {
                Jump();
                SetState(2);
                return true;
            }

        if (state == 3)
        {
            bool res = false;

            if (this->state >= 2 && this->state <= 6)
            {
                return true;
            }
            if (this->state == 0 || this->state == 1)
            {
                SetState(3);
                return true;
            }
        }

    }
    return false;
}

void Player::ProcessInput()
{
    short state = input->GetState();
    if (state & 1)
    {
        SendState(2); // jump
    }
    if (state & 2)
    {
        // useless to "go down"
    }
    if (state & 4)
    {
        if (SendState(3)) {
            speedX -= 0.01;
        }
    }
    if (state & 8)
    {
        if (SendState(3)) {
            speedX += 0.01;
        }
    }
}

void Player::ProcessNextPos()
{
    speedY += 0.01;
    if (onGround)
        speedX *= 0.96;
    else
        speedX *= 0.98;
    //speedY *= 0.96;

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
        SendState(0);
    }
}


SMALL_RECT Player::GetRectNextX()
{
    return { (short)nextX, (short)y, (short)(sprites[state]->w + nextX), (short)(sprites[state]->h + y) };
}

SMALL_RECT Player::GetRectNextY()
{
    return { (short)x, (short)nextY, (short)(sprites[state]->w + x), (short)(sprites[state]->h + nextY) };
}

void Player::UpdatePos()
{
    x = nextX;
    y = nextY;
}

void Player::Jump()
{
    this->speedY = -0.5;
}

unsigned long Player::GetElapsedMs()
{
    LARGE_INTEGER timeNow;
    QueryPerformanceCounter(&timeNow);
    LONGLONG elapsedLong = timeNow.QuadPart - lastUpdateTime.QuadPart;

    unsigned long elapsed = (unsigned long)((float)elapsedLong / (float)freq);
    return elapsed;
}