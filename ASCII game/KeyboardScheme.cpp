#include "KeyboardScheme.h"


short KeyboardScheme::GetState()
{
	short state = 0;
	/*bool up = GetKeyState(this->key_up) && (1 << 15);
	bool down = GetKeyState(this->key_down) && (1 << 15);
	bool left = GetKeyState(this->key_left) && (1 << 15);
	bool right = GetKeyState(this->key_right) && (1 << 15);
	*/
	state += (GetKeyState(this->key_up) & (1 << 15)) >> 15;
	state += (GetKeyState(this->key_down) & (1 << 15)) >> 14;
	state += (GetKeyState(this->key_left) & (1 << 15)) >> 13;
	state += (GetKeyState(this->key_right) & (1 << 15)) >> 12;

	return state;
}