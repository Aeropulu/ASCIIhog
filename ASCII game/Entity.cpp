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
	return { (short)x, (short)y, (short)(sprite.w + x), (short)(sprite.h + y) };
}

void Entity::Draw()
{
	this->buffer.Draw(this->x, this->y, this->sprite.w, this->sprite.h, this->sprite.c);
}