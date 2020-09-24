#pragma once
#include <Windows.h>
class ConsoleBuffer
{
	public:
		ConsoleBuffer(CHAR_INFO* BUFFER, int WIDTH, int HEIGHT) : buffer(BUFFER), w(WIDTH), h(HEIGHT) {};
		int const w, h;
		CHAR_INFO* buffer;
		void Draw(int, int, int, int, CHAR_INFO*, CHAR_INFO key = { ' ', 0 });
		void Clear();
};

