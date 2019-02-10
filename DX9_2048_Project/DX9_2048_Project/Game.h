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

//	C++ Includes
//
#include <map>
#include <string>

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
#include "Object.h"
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
	FPS				avgFPS;
	Mouse			mouse;
	Object			testObject;
	Object			testTile[4][4];
//	DirectX
//
	IDirect3DDevice9*	device = NULL;
	ID3DXFont*			font = NULL;
	LPD3DXEFFECT		mainShader = NULL;
	unsigned int		mrt;	//multi rendering texture Count
	std::map<std::string, IDirect3DTexture9*> texture;
	D3DXMATRIXA16		orthoMatrix;

//	Msg Print
//
	char				str[MSGPRINTMAXSIZE];
	RECT				FontBox;

	unsigned int		boardData[4][4];

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
	void MsgPrint(const unsigned int _x, const unsigned int _y);
	void ShaderLoad(std::string _name, LPD3DXEFFECT& _shader);
	void TextureLoad(std::string _filename, std::string _filepath);

//	TODO Functions
	void MoveTile(unsigned int _input);
	bool GameOver();
	void SameTile();
	void NewTile();
	void GetScore();
	void NewGame();

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
	friend class Object;
};

#endif
extern Game game;