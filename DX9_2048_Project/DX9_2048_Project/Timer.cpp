#include "Timer.h"
#include "Game.h"

void Timer::Initialize()
{
	game.debugConsole.SetFunction("Timer::Initialize");
	startTime = GetTickCount64();
	game.debugConsole << con::info << con::func << "End init" << con::endl;
	game.debugConsole.RestoreFunction();
}
void Timer::Release()
{
	return;
}
void Timer::ResetTime()
{
	startTime = GetTickCount64();
}
float Timer::getTime()
{
	return (GetTickCount64() - startTime) * 0.001f;
}
Timer::Timer()
{
}

Timer::~Timer()
{
}
