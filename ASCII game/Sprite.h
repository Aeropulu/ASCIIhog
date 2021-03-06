#pragma once
#include <Windows.h>
#include <map>


class Sprite
{
	public:

		Sprite(CHAR_INFO* chars, int width, int height) : c(chars), w(width), h(height) {}
		Sprite() : c(nullptr), w(0), h(0) {}

		CHAR_INFO*  c;
		int w, h;
		

		static std::vector<Sprite *> FromFile(std::string);
		static std::vector<Sprite *> FromFile(std::string, const std::map<char, WORD>&);
};

