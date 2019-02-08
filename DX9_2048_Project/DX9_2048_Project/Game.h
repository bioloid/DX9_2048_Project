#ifndef __GAME_H__
#define __GAME_H__

#ifdef _DEBUG
#define CONSOLEUSE true
#else
#define CONSOLEUSE false
#endif


#ifdef DEBUGCONSOLE
#define CONDEBUG true
#endif

#define MSGPRINTMAXSIZE 128


//	DirectX Includes
//
#include <d3d9.h>
#include <d3dx9.h>

//	Class Includes
//
#include "WindowClass.h"
#include "DebugConsole.h"
#include "Keyboard.h"
#include "cpu.h"
#include "Ram.h"
#include "Timer.h"
#include "FPS.h"
#include "Mouse.h"

class Game
{
private:

//	Class
//
	Keyboard		keyboard;
	WindowClass		window;
	DebugConsole	debugConsole;
	Ram				memory;
	CPU				cpu;
	Timer			mainTimer;
	FPS				avgFPS, instFPS;
	Mouse			mouse;
//	DirectX
//
	IDirect3DDevice9*	device = NULL;
	ID3DXFont*			font = NULL;
	unsigned int	mrt;

//	Msg Print
//
	char				str[MSGPRINTMAXSIZE];
	RECT				FontBox;

public:
	bool				bRunGame = true;
	bool				bConUsage = CONSOLEUSE;


public:
	void Initialize
	(int _screenX, int _screenY, HINSTANCE _hInstance, HINSTANCE _prevInstance, LPSTR _cmdLine, int _showCmd);
	
	void RunGame();
	void Release();
	void EndGame();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	void D3DXInitialize();
	void Render();
	void DrawInfo();
	void MsgPrint(const unsigned int x, const unsigned int y);
public:
	Game();
	~Game();
	friend void WindowClass::Initialize(int _screenX, int _screenY, HINSTANCE _hInstance, HINSTANCE _prevInstance, LPSTR _cmdLine, int _showCmd);
	friend void DebugConsole::Initialize(int _screenX, int _screenY);
	friend void CPU::Initialize();
	friend void Ram::Initialize();
	friend void Keyboard::Initialize();
	friend void Timer::Initialize();
	friend void FPS::Initialize(bool _mode);
	friend void Mouse::Initialize();

};

#endif
extern Game game;