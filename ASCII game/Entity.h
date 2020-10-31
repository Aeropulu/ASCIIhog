#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include "ConsoleBuffer.h"
#include "Sprite.h"

class Entity
{
public:
	Entity(ConsoleBuffer b, Sprite** s, float posX, float posY) : buffer(b), sprites(s), x(posX), y(posY) { };
	float			x, y, startX = 1, startY = 1;
	int				state = 0;
	bool			flipped = false;
	int				sizeX = 1, sizeY = 1;
	ConsoleBuffer	buffer;
	Sprite**		sprites;
	std::pair<bool, bool>			Draw(CHAR_INFO key = { ' ', 0 }, bool testHit = false);
	int				Overlap(SMALL_RECT first, SMALL_RECT second);
	SMALL_RECT		GetRect();
};

