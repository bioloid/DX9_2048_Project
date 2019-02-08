#include "FPS.h"
#include "Game.h"
FPS::FPS()
{
}

FPS::~FPS()
{
}

void FPS::Initialize(bool _mode)
{
	game.debugConsole.SetFunction("FPS::Initialize");
	mode = _mode;
	time.Initialize();
	frameCount = 0;
	game.debugConsole << con::info << con::func << "End init" << con::endl;

	game.debugConsole.RestoreFunction();
}
void FPS::Release()
{
	return;
}
void FPS::Reset()
{
	time.ResetTime();
	frameCount = 0;
}
void FPS::Count()
{
	if (mode == INST)
	{
		if (frameCount > RESETCOUNT)
		{
			frameCount = 0;
			time.ResetTime();
		}
		else
		{
			frameCount++;
		}
	}
	else
	{
		frameCount++;
	}
}
float FPS::Get()
{
	return frameCount / (time.getTime() + 0.001f);
}