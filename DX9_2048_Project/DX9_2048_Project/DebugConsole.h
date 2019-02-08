#ifndef __DEBUGCONSOLE_H__
#define __DEBUGCONSOLE_H__

#define PRINTSIZE 26
#define MAXFILEREAD 256

#define CONSOLE_VER 1.1
#define RENDERING_VER 1.5

#include<string>
#include<Windows.h>
#include<list>
#include<map>

class WindowClass;

namespace con
{
	struct FUNC_ { FUNC_() {} };
	struct ENDL_ { ENDL_() {} };
	struct INFO_ { INFO_() {} };
	struct ERROR_ { ERROR_() {} };
	struct MSG_ { MSG_() {} };

	extern ENDL_ endl;
	extern FUNC_ func;
	extern INFO_ info;
	extern ERROR_ error;
	extern MSG_ msg;
}
class DebugConsole
{
private:
	HWND			consoleHND;
	RECT			conSize;
	std::string defaultPath = "ConsoleData\\";
	std::map<std::string, std::list<std::string>> checkData;
	std::string			function;
	std::string			function_before;

	std::list<std::string>	history;
	std::list<std::string>::iterator hisptr;

	std::string			userinput;
	std::list<std::string>	outinput;
	std::list<std::string>	tabData;

public:
	void Input();
	void Check();

	void Initialize(int _screenX, int _screenY);
	void Release();
	void SetFunction(std::string);
	void RestoreFunction();
	void PrintFunctionName();
	bool IsStr(std::string);

	DebugConsole& operator<<(int);
	DebugConsole& operator<<(std::string);
	DebugConsole& operator<<(float);
	DebugConsole& operator<<(double);
	DebugConsole& operator<<(con::ENDL_);
	DebugConsole& operator<<(con::FUNC_);
	DebugConsole& operator<<(con::INFO_);
	DebugConsole& operator<<(con::ERROR_);
	DebugConsole& operator<<(con::MSG_);
	DebugConsole& operator<<(POINT);

	DebugConsole();
	~DebugConsole();

	friend class WindowClass;
};


#endif // !__DEBUGCONSOLE_H__