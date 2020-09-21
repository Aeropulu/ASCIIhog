#pragma once
#include <Windows.h>
#include "ConsoleBuffer.h"
class Entity
{
public:
	Entity(ConsoleBuffer b, float posX, float posY) : x(posX), y(posY), buffer(b) { };
	float			x, y;
	ConsoleBuffer const	buffer;
	virtual void Draw() = 0;
	virtual bool CollideWith(Entity other) = 0;
};

