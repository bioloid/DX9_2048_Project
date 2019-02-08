#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__
#include <Windows.h>
#define MAXKEYCOUNT 128

class Keyboard
{
private:
	bool keyboard[MAXKEYCOUNT];
public:
	void Initialize();
	void Release();
	bool IsKeyDown(WPARAM _key);
	void KeyDown(WPARAM _key);
	void KeyUp(WPARAM _key);
	void KeyEvent();
public:
	Keyboard();
	~Keyboard();
};

#endif