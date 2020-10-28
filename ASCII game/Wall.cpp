#include "Wall.h"

Wall::Wall(ConsoleBuffer b, float posX, float posY, int const sizeX, int const sizeY) : Entity(b, GenerateSprite(sizeX, sizeY), posX, posY) {
	this->sizeX = sizeX;
	this->sizeY = sizeY;
}

Wall::~Wall() {
	free(sprites[0]); // "Wall" creates his own Sprite so he needs to handle the freeing of the memory, there is only one sprite in a Wall. Doesn't work
}

Sprite** Wall::GenerateSprite(int const width, int const height) {
	CHAR_INFO* c = (CHAR_INFO*)malloc(sizeof(CHAR_INFO) * width * height);
	Sprite** result = new Sprite*[1];
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
				c[i + j * width].Attributes = 0x00;
			}
		}
	}
	result[0] = new Sprite(c, width, height);
	return result;
}
