#ifndef __WINDOWCLASS_H__
#define __WINDOWCLASS_H__


#include <Windows.h>
#include <string>

class DebugConsole;
class Game;
class WindowClass
{
private:
	HWND				hwnd;
	HINSTANCE			hInstance;
	HINSTANCE			prevInstance;
	LPSTR				cmdLine;
	WNDCLASS			wc;
	int					showCmd;
	std::string			programName;
	MSG					msg;
	RECT				winSize;
	char				programPath[MAX_PATH];	// MAX_PATH from Windows.h Header
	int					EndWaitTime = 3;	// Engine END time in ms
public:
	void Initialize(int _screenX, int _screenY, HINSTANCE _hInstance, HINSTANCE _prevInstance, LPSTR _cmdLine, int _showCmd);
	void Release();


public:
	WindowClass();
	~WindowClass();

	friend class DebugConsole;
	friend class Game;
};

#endif