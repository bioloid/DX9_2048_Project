//	WIN API Include
//
#include <Windows.h>

//	CRT DEBUG Include
//
#include "CRT_DEBUG.h"

//	CLASS Include
//
#include "Game.h"

//	Other Include
//
#include "Defines.h"

Game game;

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _prevInstance, LPSTR _cmdLine, int _showCmd)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//	_CrtSetBreakAlloc(469);
#endif
	game.Initialize(WINDOWSIZE_X, WINDOWSIZE_Y, _hInstance, _prevInstance, _cmdLine, _showCmd);
	game.RunGame();

	game.Release();

	return 0;
}