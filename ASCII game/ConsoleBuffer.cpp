#include "ConsoleBuffer.h"

void ConsoleBuffer::Draw(int x, int y, int width, int height, CHAR_INFO* data)
{
	CHAR_INFO* p = data;
	for (int i = y; i < y + height; i++)
	{
		for (int j = x; j < x + width; j++)
		{
			this->buffer[j + i * this->w] = *p++;
		}
	}
}

void ConsoleBuffer::Clear()
{
	for (int i = 0; i < this->h; i++)
	{
		for (int j = 0; j < this->w; j++)
		{
			this->buffer[j + i * this->w].Char.UnicodeChar = ' ';
		}
	}
	//size_t	size = sizeof(*this->buffer)*this->w*this->h;
	//memset(this->buffer, 0, size);
}