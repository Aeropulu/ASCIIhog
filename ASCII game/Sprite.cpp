#include <vector>
#include <string>
#include <fstream>



#include "Sprite.h"


std::vector<Sprite> Sprite::FromFile(std::string filename)
{
	std::vector<Sprite> result;
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
				// TODO create sprite and push it
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

