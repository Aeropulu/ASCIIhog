#include "Wall.h"

Wall::Wall(ConsoleBuffer b, int posX, int posY, int const sizeX, int const sizeY) : Entity(b, GenerateSprite(sizeX, sizeY), posX, posY) {

}

Sprite Wall::GenerateSprite(int const width, int const height) {
	CHAR_INFO* c = (CHAR_INFO*)malloc(sizeof(CHAR_INFO) * width * height);
	for (int i = 0; i < width; ++i) 
	{
		for (int j = 0; j < height; ++j)
		{
			if (i == 0 ||j == 0 ||i == (width-1) ||j == (height-1)){
				c[i + j * width].Char.UnicodeChar = ' ';
				c[i + j * width].Attributes = 0x0020;
			} else 
			{
				c[i + j * width].Char.UnicodeChar = ' ';
				c[i + j * width].Attributes = 0x0000;
			}
		}
	}
	return Sprite(c, width, height);
}
