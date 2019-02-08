#include "Game.h"
#include "WindowClass.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return game.MessageHandler(hwnd, msg, wParam, lParam);
}


void WindowClass::Initialize(int _screenX, int _screenY, HINSTANCE _hInstance, HINSTANCE _prevInstance, LPSTR _cmdLine, int _showCmd)
{
	game.debugConsole.SetFunction("WindowClass::Initialize");

	programName = "DX9_2048_Project";
	hInstance = _hInstance;	prevInstance = _prevInstance;
	cmdLine = _cmdLine;	showCmd = _showCmd;

	winSize.right = _screenX;	winSize.left = 0;
	winSize.bottom = _screenY;	winSize.top = 0;

	GetCurrentDirectory(MAX_PATH, programPath);
	ZeroMemory(&msg, sizeof(MSG));

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = programName.c_str();
	if (!RegisterClass(&wc))
	{
		game.debugConsole << con::error << "RegisterClass - error" << con::endl;
	}

	hwnd = CreateWindow
	(programName.c_str(), programName.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 
		winSize.right, winSize.bottom, 0, 0, hInstance, 0);
	if (!hwnd)
	{
		game.debugConsole << con::error << "CreateWindow - error" << con::endl;
	}

	MoveWindow(hwnd, 0, 0, winSize.right, winSize.bottom, TRUE);
	ShowWindow(hwnd, SW_SHOW); //	SW_SHOW, SW_SHOWMAXIMIZED
	MoveWindow(game.debugConsole.consoleHND, 
		winSize.right + game.debugConsole.conSize.left, game.debugConsole.conSize.top,
		game.debugConsole.conSize.right, game.debugConsole.conSize.bottom, TRUE);

	game.debugConsole << con::info << con::func << "End init" << con::endl;
	game.debugConsole.RestoreFunction();
}

void WindowClass::Release()
{
	ShowWindow(hwnd, SW_SHOWMINIMIZED);

	while (EndWaitTime > 0)
	{
		Sleep(1000);
		EndWaitTime--;
	}
}

WindowClass::WindowClass()
{
}


WindowClass::~WindowClass()
{
}

