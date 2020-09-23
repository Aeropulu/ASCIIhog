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
	return { (short)x, 
		(short)y, 
		(short)(sprites[state]->w + x), 
		(short)(sprites[state]->h + y) };
}

void Entity::Draw()
{
	buffer.Draw(
		x, 
		y, 
		sprites[state]->w, 
		sprites[state]->h, 
		sprites[state]->c);
		
}