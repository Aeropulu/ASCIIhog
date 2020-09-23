#pragma once
#include <Windows.h>
#include "ConsoleBuffer.h"
#include "Sprite.h"

class Entity
{
public:
	Entity(ConsoleBuffer b, Sprite s, float posX, float posY) : buffer(b), sprite(s), x(posX), y(posY) { };
	float			x, y;
	ConsoleBuffer	buffer;
	Sprite			sprite;
	void			Draw();
	int				Overlap(SMALL_RECT first, SMALL_RECT second);
	SMALL_RECT		GetRect();
};

