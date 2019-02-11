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

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

//	C++ Includes
//
#include <map>
#include <string>
#include <vector>
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
	Object			mainScreen;
	Object			newGameButton;
	std::vector<Object> tile;
//	Object			testTile[4][4];
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

	Object*				boardData[4][4];
	unsigned int		score;

public:
	bool				bLoseGame = false;
	bool				bWinGame = false;
	bool				bEndGame = true;
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

	void NewTile();
	void NewGame();
	void DrawScore();
	void DrawEndMsg();
	void MoveTile(unsigned int _input);
	bool SameTile(int _x1, int _y1, int _x2, int _y2);
	bool GameOver();

public:
	Game();
	~Game();
	friend void WindowClass::Initialize(int _screenX, int _screenY, HINSTANCE _hInstance, HINSTANCE _prevInstance, LPSTR _cmdLine, int _showCmd);
	friend void DebugConsole::Initialize(int _screenX, int _screenY);
	friend void CPU::Initialize();
	friend void Ram::Initialize();
	friend void Timer::Initialize();
	friend void FPS::Initialize(bool _mode);
	friend class Mouse;
	friend class Object;
	friend class Keyboard;
};

#endif
extern Game game;