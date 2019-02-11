#include "Game.h"
#include "DebugConsole.h"
#include <iostream>
#include <conio.h> //_getch(), _kbhit()
#include <fstream>
#include <stdio.h>


#pragma warning(disable:4267)
#pragma warning(disable:4244)
#pragma warning(disable:4996)

using namespace std;
namespace con
{
	ENDL_	endl;
	FUNC_	func;
	INFO_	info;
	ERROR_	error;
	MSG_	msg;
}
DebugConsole::DebugConsole()
{
}

DebugConsole::~DebugConsole()
{
}

//	Console Event Handler
//
bool CtrlHandler(DWORD fdwCtrlType)
{
	switch (fdwCtrlType)
	{
	case CTRL_C_EVENT:
		return FALSE;
	case CTRL_CLOSE_EVENT:
		game.bLoseGame = false;
		Sleep(1000 * 1000);
		return FALSE;

	default:
		return FALSE;
	}
}
bool DebugConsole::IsStr(string _data)
{
	for (auto ptr = _data.begin(); ptr != _data.end(); ptr++)
	{
		if (*ptr < 48 && *ptr > 57)
			return true;
	}
	return false;
}

void DebugConsole::Input()
{
	if (_kbhit())
	{
		char data = _getch();
		if (data == -32) // πÊ«‚≈∞
		{
			list<string>::iterator tmp;
			data = _getch();
			if (data == 72) // up
			{
				if (history.size() > 1)
				{
					tmp = hisptr;
					if (++tmp != history.end())
					{
						hisptr++;
						for (int i = 0; i < userinput.length(); i++)
							cout << "\b" << " " << "\b";
						userinput = *hisptr;
						cout << userinput;
					}
				}
			}
			else if (data == 80) // down
			{
				if (history.size() > 1)
				{
					if (hisptr != history.begin())
					{
						tmp = hisptr;
						if (--tmp != history.begin())
						{
							hisptr--;
							for (int i = 0; i < userinput.length(); i++)
								cout << "\b" << " " << "\b";
							userinput = *hisptr;
							cout << userinput;
						}
					}
				}
			}
			else if (data == 75) { // left
			}
			else if (data == 77) { // right
			}
		}
		else if (data == 13) // enter
		{
			if (!userinput.empty())
			{
				cout << endl;
				while (userinput.back() == ' ')
					userinput.pop_back();

				userinput += '\0';
				outinput.clear();
				int start, end, length = userinput.length();
				for (start = end = 0; start < length && end < length; end++)
				{
					if (userinput[end] == ' ' || userinput[end] == '\0')
					{
						string tmp;
						for (int i = start; i < end; i++)
							tmp += userinput[i];
						outinput.push_back(tmp);
						start = end + 1;
					}
				}
				userinput.pop_back();
				history.pop_front();
				history.push_front(userinput);
				history.push_front(" ");
				hisptr = history.begin();
				userinput.clear();
				Check();
				if (game.bLoseGame == true)
					cout << ">> ";
			}
		}
		else if (data == 9) // tab
		{
			if (!userinput.empty())
			{
				int spacebar = userinput.rfind(" ");
				int pos;
				//	cout << spacebar;

				char data[4];
				data[3] = '\0';
				for (auto ptr = tabData.begin(); ptr != tabData.end(); ptr++)
				{
					for (int i = 0; i < 3; i++)
						data[i] = (*ptr)[i];

					pos = userinput.rfind(data);
					if (pos > spacebar)
					{
						int len = userinput.length();
						for (int i = 0; i < len - spacebar - 1; i++)
						{
							cout << "\b" << " " << "\b";
							userinput.pop_back();
						}
						cout << *ptr << " ";
						userinput += *ptr;
						userinput += " ";
						break;
					}
				}
			}
		}
		else if (data == 8) // backspace
		{
			if (userinput.length() > 0) {
				userinput.pop_back();
				cout << "\b" << " " << "\b";
			}
		}
		else if (data == 32)
		{
			if (userinput.back() != ' ')
			{
				userinput += data;
				cout << data;
			}
		}
		else				// normal input, space bar
		{
			userinput += data;
			cout << data;
		}
	}
}
void DebugConsole::Check()
{
#ifdef CONDEBUG
	cout << "User Input Info" << endl;
	cout << "history" << endl;
	for (auto ptr = history.begin(); ptr != history.end(); ptr++)
		cout << *ptr << ":" << endl;

	cout << "outinput" << endl;
	for (auto ptr = outinput.begin(); ptr != outinput.end(); ptr++)
		cout << *ptr << ":" << endl;

#endif // CONDEBUG
	int count = outinput.size();
	auto ptr = outinput.begin();
	if (count == 1)
	{
		if (*ptr == "ver")
		{
			ptr = checkData["ver"].begin();
			cout << endl << *++ptr << " v" << RENDERING_VER << endl;
		}
		else if (*ptr == "exit")
		{
			game.EndGame();
		}
		else
		{
			cout << endl << checkData["error"].front() << endl;
		}
	}
	else if (count == 2)
	{
		if (*ptr == "ver")
		{
			if (*++ptr == "-c")
				cout << endl << *++(++checkData["ver"].begin()) << " v" << CONSOLE_VER << endl;
			else if (*ptr == "-h")
				cout << endl << checkData["ver"].front() << endl;
			else
				cout << endl << checkData["error"].front() << endl;
		}
		else
		{
			cout << endl << checkData["error"].front() << endl;
		}
	}
	else
	{
		cout << endl << checkData["error"].front() << endl;
	}
	cout << endl;
}

void DebugConsole::Initialize(int _screenX, int _screenY)
{
	SetFunction("DebugConsole::Initialize");

	conSize.right = _screenX;	conSize.left = 0;
	conSize.bottom = _screenY;	conSize.top = 0;
	

	if (game.bConUsage == true)
	{
		AllocConsole();
		SetConsoleTitle("Debug Console");
		consoleHND = GetForegroundWindow();

		freopen("CONOUT$", "w", stdout);
		freopen("CONIN$", "r", stdin);
		freopen("CONERR$", "w", stderr);

		if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE))
		{
			game.bConUsage = false;
		}
	}
	*this << con::info << con::func << "console started" << con::endl;

	//	Read console tab data txt file
	//
	std::ifstream file;
	string tmpPath;
	char input;
	string fileReadData;

	tmpPath = defaultPath;
	tmpPath += "CONSOLE_TAB_DATA.txt";
	file.open(tmpPath);

	if (file.fail())
	{
		file.clear();
		file.close();
		*this << con::error << con::func << "CONSOLE_TAB_DATA.txt open() - failed" << con::endl;
		*this << con::error << con::func << "console tab function disabled" << con::endl;
	}

	else
	{
		while (!file.eof())
		{
			file >> fileReadData;
			tabData.push_back(fileReadData);
		}
		file.clear();
		file.close();
		*this << con::info << con::func << "tab data load - succeed" << con::endl;
	}



	//	Read console check data txt file
	//
	file.open(defaultPath + "CONSOLE_CHECK_DATA.txt");
	if (file.fail())
	{
		file.clear();
		file.close();
		*this << con::error << con::func << "CONSOLE_CHECK_DATA open() - failed" << con::endl;
		*this << con::error << con::func << "console is now disabled" << con::endl;
		game.bConUsage = false;
		DestroyWindow(consoleHND);
	}

	else
	{
		int num;
		list<string>		tmp_list;
		string				fileReadData_;
		map<string, list<string>> tmp_map;
		while (!file.eof())
		{
			file.get(input);
			if (input == ':')
			{
				file >> num;
				file >> fileReadData;
				file.get();
				for (int i = 0; i < num; i++)
				{
					fileReadData_.clear();
					while (true)
					{
						file.get(input);
						if (input == '\n' || file.eof())
							break;
						if (input == '\\')
						{
							file.get(input);
							if (input == '\n')
								break;
							if (input == 'n')
								fileReadData_ += '\n';
							else
							{
								fileReadData_ += '\\';
								fileReadData_ += input;
							}
						}
						else
							fileReadData_ += input;
					}
					tmp_list.push_back(fileReadData_);
				}
				checkData[fileReadData] = tmp_list;
				tmp_list.clear();
			}
		}
		file.clear();
		file.close();
		*this << con::info << con::func << "check data load - succeed" << con::endl;
		history.push_front(" ");
		*this << con::info << con::func << "console history ready" << con::endl;

		hisptr = history.begin();
		*this << con::info << con::func << "End init" << con::endl;

	}
	RestoreFunction();
}
void DebugConsole::Release()
{
	if (game.bConUsage == true)
		FreeConsole();
}

void DebugConsole::SetFunction(string _function)
{
	if (game.bConUsage == true)
	{
		function_before = function;
		function = _function;
	}
}
void DebugConsole::RestoreFunction()
{
	if (game.bConUsage == true)
	{
		function = function_before;
	}
}

void DebugConsole::PrintFunctionName()
{
	if (game.bConUsage == false)
		return;

	if (function.length() <= 0)
		return;
	else
	{
		if (function.length() > PRINTSIZE)
			cout << " :" << function << ": ";
		else
		{
			int front = PRINTSIZE - (int)function.length();
			int back = front;
			front = front / 2;
			back = back - front;
			cout << " :";
			for (int i = 0; i < front; i++)
				cout << " ";
			cout << function;
			for (int i = 0; i < back; i++)
				cout << " ";
			cout << ": ";
		}
	}
}

DebugConsole& DebugConsole::operator<<(string _data)
{
	if (game.bConUsage == true)
		cout << _data;
	return *this;
}
DebugConsole& DebugConsole::operator<<(int _data)
{
	if (game.bConUsage == true)
		cout << _data;
	return *this;
}
DebugConsole& DebugConsole::operator<<(float _data)
{
	if (game.bConUsage == true)
		cout << _data;
	return *this;
}
DebugConsole& DebugConsole::operator<<(double _data)
{
	if (game.bConUsage == true)
		cout << _data;
	return *this;
}
DebugConsole& DebugConsole::operator<<(con::ENDL_ _data)
{
	if (game.bConUsage == true)
		cout << std::endl;
	return *this;
}
DebugConsole& DebugConsole::operator<<(con::FUNC_ _data)
{
	if (game.bConUsage == true)
		PrintFunctionName();
	return *this;
}
DebugConsole& DebugConsole::operator<<(con::INFO_ _data)
{
	if (game.bConUsage == true)
		cout << ":INFO";
	return *this;
}
DebugConsole& DebugConsole::operator<<(con::ERROR_ _data)
{
	if (game.bConUsage == true)
		cout << ":ERROR";
	return *this;
}
DebugConsole& DebugConsole::operator<<(con::MSG_ _data)
{
	if (game.bConUsage == true)
		cout << ":MSG ";
	return *this;
}
DebugConsole& DebugConsole::operator<<(POINT _data)
{
	if (game.bConUsage == true)
		cout << "x : " << _data.x << " y : " << _data.y;
	return *this;
}
