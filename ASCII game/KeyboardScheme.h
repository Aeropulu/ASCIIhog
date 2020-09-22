#include <Windows.h>
#include <WinUser.h>
#include "InputScheme.h"

class KeyboardScheme : public InputScheme
{
	public:
		KeyboardScheme() : key_up(VK_UP), key_down(VK_DOWN), key_left(VK_LEFT), key_right(VK_RIGHT) {};
		short GetState();

	private:
		int key_up, key_down, key_left, key_right;
};