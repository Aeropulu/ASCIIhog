#pragma once
#include <Windows.h>

class Sprite
{
	public:
		Sprite(CHAR_INFO* chars, int width, int height) : c(chars), w(width), h(height) {}
		CHAR_INFO* const c;
		int w, h;
};

