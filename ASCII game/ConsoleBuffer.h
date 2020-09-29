#pragma once
#include <Windows.h>
#include <utility>
class ConsoleBuffer
{
	public:
		ConsoleBuffer(CHAR_INFO* BUFFER, int WIDTH, int HEIGHT) : buffer(BUFFER), w(WIDTH), h(HEIGHT) {};
		int const w, h;
		CHAR_INFO* buffer;
		std::pair<bool, bool> Draw(int, int, int, int, CHAR_INFO*, CHAR_INFO key = { ' ', 0 }, bool flipped = false, bool testHit = false, char charTest = '+' );
		std::pair<bool, bool> DrawIntern(CHAR_INFO*, CHAR_INFO, char, int, int, bool);
		void Clear();
};

