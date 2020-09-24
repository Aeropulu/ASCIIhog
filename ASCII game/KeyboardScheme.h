#include <Windows.h>
#include <WinUser.h>
#include "InputScheme.h"

class KeyboardScheme : public InputScheme
{
	public:
		KeyboardScheme(int up = VK_UP, int down = VK_DOWN, int left = VK_LEFT, int right = VK_RIGHT)
			: key_up(up), key_down(down), key_left(left), key_right(right) {};
		short GetState();

	private:
		int key_up, key_down, key_left, key_right;
};