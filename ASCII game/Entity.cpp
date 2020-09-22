#include "Entity.h"


int Entity::Overlap(Entity other)
{
	SMALL_RECT otherRect = other.getRect();
	SMALL_RECT thisRect = getRect();

	if (otherRect.Left > thisRect.Right || thisRect.Left > otherRect.Right)
		return 0;
	if (otherRect.Top > thisRect.Bottom || thisRect.Top > otherRect.Bottom)
		return 0;

	return 1;
}

SMALL_RECT Entity::getRect()
{
	return { (short)x, (short)y, (short)(sprite.w + x), (short)(sprite.h + y)};
}

void Entity::Draw()
{
	this->buffer.Draw(this->x, this->y, this->sprite.w, this->sprite.h, this->sprite.c);
}