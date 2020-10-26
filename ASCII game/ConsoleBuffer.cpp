#include "ConsoleBuffer.h"

// returns a pair of bool telling if the entity {self, other} are being drawn over the char "charCollision"
std::pair<bool, bool> ConsoleBuffer::Draw(int x, int y, int width, int height, CHAR_INFO* data, CHAR_INFO key, bool flipped, bool testHit, char charCollision)
{
	CHAR_INFO* p = data;

	std::pair<bool, bool> resultCollision = { false, false };
	if (!flipped)
	{
		for (int i = y; i < y + height; i++)
		{
			for (int j = x; j < x + width; j++)
			{
				if (testHit)
				{
					std::pair<bool, bool> tmp = DrawIntern(p, key, charCollision, i, j, true);
					if (tmp.first)
						resultCollision.first = true;
					if (tmp.second)
						resultCollision.second = true;
				} else 
				{
					DrawIntern(p, key, charCollision, i, j, false);
				}
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
				if (testHit)
				{
					std::pair<bool, bool> tmp = DrawIntern(p, key, charCollision, i, j, true);
					if (tmp.first)
						resultCollision.first = true;
					if (tmp.second)
						resultCollision.second = true;
				} else 
				{
					DrawIntern(p, key, charCollision, i, j, false);
				}
				p++;
			}
		}
	}
	return resultCollision;
	
}

std::pair<bool, bool> ConsoleBuffer::DrawIntern(CHAR_INFO* p, CHAR_INFO key, char charCollision, int i, int j, bool testHit)
{
	std::pair<bool, bool> result = { false, false };
	if (p->Attributes != key.Attributes || p->Char.UnicodeChar != key.Char.UnicodeChar)
	{
		if (j >= 0 && j < w && i >= 0 && i < h)
		{
			if (testHit)
			{
				char currentChar = this->buffer[j + i * this->w].Char.UnicodeChar;
				if (currentChar != ' ' && currentChar != '-') // ignore white space and blade
				{
					char newChar = p->Char.UnicodeChar;
					if (currentChar == '+') { // if buffer has the charCollision
						if (newChar != ' ' && newChar != '-' && newChar != charCollision) // if charCollision is inside the entity being drawn
							result.first = true; //then self is overlaping the charCollision char
					}
					else // else then it is the other's char
					{
						if (newChar == charCollision) // if self char is the charCollision
							result.second = true;
					}
				}
			}
			

			this->buffer[j + i * this->w] = *p;
		}
	}
	return result;
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