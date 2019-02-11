#include "Keyboard.h"
#include "Game.h"


void Keyboard::Initialize()
{
	game.debugConsole.SetFunction("Keyboard::Initialize");
	for (int i = 0; i < MAXKEYCOUNT; i++)
		keyboard[i] = false;
	game.debugConsole << con::info << con::func << "End init" << con::endl;
	game.debugConsole.RestoreFunction();
}

void Keyboard::Release()
{
	return;
}

bool Keyboard::IsKeyDown(WPARAM _key)
{
	return keyboard[_key];
}

void Keyboard::KeyDown(WPARAM _key)
{
	if (_key < MAXKEYCOUNT)
		keyboard[_key] = true;
	if (_key == VK_UP)
		game.MoveTile(UP);
	else if (_key == VK_DOWN)
		game.MoveTile(DOWN);
	else if (_key == VK_RIGHT)
		game.MoveTile(RIGHT);
	else if (_key == VK_LEFT)
		game.MoveTile(LEFT);
	else
	{
		if (_key != VK_ESCAPE)
			game.NewTile();
		else
			game.EndGame();
	}
}

void Keyboard::KeyUp(WPARAM _key)
{
	if (_key < MAXKEYCOUNT)
		keyboard[_key] = false;
}

void Keyboard::KeyEvent()
{
}

Keyboard::Keyboard()
{
}


Keyboard::~Keyboard()
{
}
