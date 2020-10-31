#include "Entity.h"


int Entity::Overlap(SMALL_RECT first, SMALL_RECT second)
{

	if (second.Left >= first.Right || first.Left >= second.Right)
		return 0;
	if (second.Top >= first.Bottom || first.Top >= second.Bottom)
		return 0;

	return 1;
}

SMALL_RECT Entity::GetRect()
{
	return { (short)(x - (sizeX / 2)),
		(short)y, 
		(short)(sizeX/2 + x), 
		(short)(sprites[state]->h + y) };
}

std::pair<bool, bool> Entity::Draw(CHAR_INFO key, bool testHit)
{
	return buffer.Draw(
		(int)x-(sprites[state]->w/2), 
		(int)y, 
		sprites[state]->w, 
		sprites[state]->h, 
		sprites[state]->c,
		key, flipped, testHit);
}