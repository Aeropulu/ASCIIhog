#include <Windows.h>
#include "Player.h"
#include "KeyboardScheme.h"
#include "Wall.h"

Player::Player(ConsoleBuffer b, Sprite** s, float posX, float posY, InputScheme *scheme) : Entity(b, s, posX, posY)
{
    if (!scheme)
        input = new KeyboardScheme();
    else
        input = scheme;
    speedX = 0;
    speedY = 0;
    startX = x;
    startY = y;
    nextX = x;
    nextY = y;
    sizeX = 10;
    sizeY = 7;
    QueryPerformanceCounter(&lastUpdateTime);
    LARGE_INTEGER li_freq;
    QueryPerformanceFrequency(&li_freq);
    freq = li_freq.QuadPart;
    freq /= 1000;
}

void Player::ProcessState()
{

    if (!onGround)
        SendState(2);

    switch(state)
    {
        case 0: // idle state
            break;
        case 1: // recovery time
            if (GetElapsedMs() >= 400)
                SetState(0);
            break;
        case 2: // falling
            SetState(2);
            break;
        case 3: // running frame 1
            if (GetElapsedMs() >= 150)
            {
                SetState(4);
            }
            break;
        case 4: // running frame 2
            if (GetElapsedMs() >= 150)
            {
                SetState(5);
            }
            break;
        case 5: // running frame 3
            if (GetElapsedMs() >= 150)
            {
                SetState(6);
            }
            break;
        case 6: // running frame 4
            if (GetElapsedMs() >= 150)
            {
                SetState(3);
            }
            break;
        case 7: // attack frame 1
            if (GetElapsedMs() >= 300)
                SetState(8);
            break;
        case 8: // attack frame 2
            if (GetElapsedMs() >= 200)
                SetState(1);
            break;
        case 9: // attack falling 
            break;
        case 10: // blocking
            if (GetElapsedMs() >= 300)
                SetState(0);
            break;
        case 11: // dead ?
            break;
    }

}

//hard Set, no checks
void Player::SetState(int state)
{
    LARGE_INTEGER timeNow;
    QueryPerformanceCounter(&timeNow);
    lastUpdateTime = timeNow;
    this->state = state;
}

//event Occured
bool Player::SendState(int newState)
{
    if (this->state != 1 && this->state <= 6)
    {
        if (newState == 0)
        {
            SetState(0);
        }

        if (newState == 1)
        {
            SetState(1);
        }

        if (newState == 2)
        {
            SetState(2);
            return true;
        }

        if (newState == 3)
        {

            if (this->state >= 2 && this->state <= 6)
            {
                return true;
            }
            if (this->state == 0)
            {
                SetState(3);
                return true;
            }
        }

        if (newState == 7 && this->state != 2)
        {
            SetState(7);
            return true;
        }
    }
    
    return false;
}

void Player::ProcessInput()
{
    short InputState = input->GetState();
    if (InputState & 1)
    {
        if (onGround && state != 1 && state <= 6)
        {
            Jump();
            SendState(2);
        }
    }
    if (InputState & 2)
    {
        // useless to "go down"
        //attack instead
        SendState(7);
    }

    bool walking = false;
    if (InputState & 4)
    {
        if (SendState(3)) {
            speedX -= 0.04f;
            walking = true;
        }
    }
    if (InputState & 8)
    {
        if (SendState(3)) {
            speedX += 0.04f;
            walking = true;
        }
    }
    if (!walking || (onGround && this->state == 2)) // if we stop walking or touch the ground
        SendState(0);
}

void Player::ProcessNextPos()
{
    speedY += 0.01;
    if (onGround)
        speedX *= 0.90f;
    else
        speedX *= 0.92f;

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
    return { (short)(nextX - (sizeX / 2)), (short)y, (short)(sizeX/2 + nextX), (short)(sizeY + y) };
}

SMALL_RECT Player::GetRectNextY()
{
    return { (short)(x - (sizeX / 2)), (short)nextY, (short)(sizeX/2 + x), (short)(sizeY + nextY) };
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

void Player::Die()
{
    SetState(11);
}

void Player::Reset()
{
    x = startX;
    y = startY;
    speedX = 0;
    speedY = 0;
    nextX = x;
    nextY = y;
    SetState(0);
}

unsigned long Player::GetElapsedMs()
{
    LARGE_INTEGER timeNow;
    QueryPerformanceCounter(&timeNow);
    LONGLONG elapsedLong = timeNow.QuadPart - lastUpdateTime.QuadPart;

    unsigned long elapsed = (unsigned long)((float)elapsedLong / (float)freq);
    return elapsed;
}