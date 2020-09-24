#include "ConsoleBuffer.h"

void ConsoleBuffer::Draw(int x, int y, int width, int height, CHAR_INFO* data, CHAR_INFO key, bool flipped)
{
	CHAR_INFO* p = data;

	if (!flipped)
	{
		for (int i = y; i < y + height; i++)
		{
			for (int j = x; j < x + width; j++)
			{
				DrawIntern(p, key, i, j);
				p++;
			}
		}
	}
	else
	{
		for (int i = y; i < y + height; i++)
		{
			for (int j = x + width -1; j >= x ; j--)
			{
				DrawIntern(p, key, i, j);
				p++;
			}
		}
	}
	
}

void ConsoleBuffer::DrawIntern(CHAR_INFO* p, CHAR_INFO key, int i, int j)
{
	if (p->Attributes != key.Attributes || p->Char.UnicodeChar != key.Char.UnicodeChar)
	{
		if (j >= 0 && j < w && i >= 0 && i < h)
			this->buffer[j + i * this->w] = *p;
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