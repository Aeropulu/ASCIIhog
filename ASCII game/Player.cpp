#include "Player.h"
#include <Windows.h>
#include "KeyboardScheme.h"

Player::Player(ConsoleBuffer b, Sprite s, float posX, float posY) : Entity(b, s, posX, posY)
{
    this->input = new KeyboardScheme();
    state = 0;
}

void Player::ProcessInput()
{
    short state = input->GetState();
    if (state & 1)
    {
        y -= 0.1;
    }
    if (state & 2)
    {
        y += 0.1;
    }
    if (state & 4)
    {
        x -= 0.1;
    }
    if (state & 8)
    {
        x += 0.1;
    }
    
}

void Player::Draw()
{
	

    this->buffer.Draw(this->x, this->y, this->sprite.w, this->sprite.h, this->sprite.c);
}