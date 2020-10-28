#include <vector>
#include <string>
#include <fstream>



#include "Sprite.h"


std::vector<Sprite *> Sprite::FromFile(std::string filename)
{
	std::vector<Sprite *> result;
	std::ifstream file(filename);
	std::vector<std::string> builder;
	while (file) // read until the stream goes bad
	{
		std::string line;
		std::getline(file, line);
		if (line.size() == 0)
		{
			if (builder.size() != 0)
			{
				int width = builder[0].size();
				int height = builder.size();
				CHAR_INFO *chars = (CHAR_INFO*)malloc(sizeof(CHAR_INFO) * width * height);
				CHAR_INFO* charitr = chars;
				for (int i = 0; i < height; i++)
				{
					for (int j = 0; j < width; j++)
					{
						CHAR_INFO c;
						c.Attributes = 0x06;
						c.Char.UnicodeChar = builder[i][j];
						if (chars)
						{
							
							*charitr = c;
							charitr++;
						}
						
					}
				}
				Sprite* spr = new Sprite(chars, width, height);
				result.push_back(spr);
				builder.clear();
			}
		}
		else
		{
			builder.push_back(line);
		}
		
	}
	
	return result;
}