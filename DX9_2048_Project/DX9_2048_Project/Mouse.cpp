#include "Mouse.h"
#include "Game.h"
#pragma warning (disable:4715)
Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}
void Mouse::Release()
{
	return;
}
void Mouse::Initialize()
{
	game.debugConsole.SetFunction("Mouse::Initialize");
	coor.x = 0; coor.y = 0;
	L = false; R = false;
	game.debugConsole << con::info << con::func << "End init" << con::endl;
	game.debugConsole.RestoreFunction();
}

void Mouse::MouseMove(LPARAM lParam)
{
	coor.x = LOWORD(lParam);
	coor.y = HIWORD(lParam);
}

void Mouse::MouseDown(WORD data, LPARAM lParam)
{
	coor.x = LOWORD(lParam);
	coor.y = HIWORD(lParam);
	if (data == MOUSE_RIGHT) {
		R = true;
		return;
	}
	else if (data == MOUSE_LEFT) {
		L = true;
		return;
	}
}
void Mouse::MouseUp(WORD data, LPARAM lParam)
{
	coor.x = LOWORD(lParam);
	coor.y = HIWORD(lParam);
	if (data == MOUSE_RIGHT) {
		R = false;
		return;
	}
	else if (data == MOUSE_LEFT) {
		L = false;
		return;
	}
}
bool Mouse::IsMouseDown(WORD data)
{
	if (data == MOUSE_RIGHT) {
		return R;
	}
	else if (data == MOUSE_LEFT) {
		return L;
	}
}
POINT Mouse::MousePosition()
{
	return coor;
}

int Mouse::IsMouseWheel(WPARAM data)
{
	if ((SHORT)HIWORD(data) > 0) {
		return MOUSE_UP;
	}
	else {
		return MOUSE_DOWN;
	}
}