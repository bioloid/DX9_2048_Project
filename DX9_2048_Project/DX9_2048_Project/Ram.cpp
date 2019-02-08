#include <iostream>
#include "RAM.h"
#include "Game.h"
Ram::Ram()
{
}

Ram::~Ram()
{
}
void Ram::Initialize()
{
	game.debugConsole.SetFunction("Ram::Initialize");
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *)&g_mc, sizeof(g_mc));
	game.debugConsole << con::info << con::func << "End init" << con::endl;
	game.debugConsole.RestoreFunction();
}
void Ram::Release()
{
	return;
}
void Ram::Update()
{
	if ((m_lastSampleTime + REFRESHTIME) < GetTickCount())
	{
		m_lastSampleTime = GetTickCount();

		memInfo.dwLength = sizeof(MEMORYSTATUSEX);
		GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *)&pmc, sizeof(pmc));
		GlobalMemoryStatusEx(&memInfo);
		totalVirtualMem = memInfo.ullTotalPageFile;
		virtualMemUsed = memInfo.ullTotalPageFile - memInfo.ullAvailPageFile;
		virtualMemUsedByMe = pmc.PrivateUsage;
		totalPhysMem = memInfo.ullTotalPhys;
		physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
		physMemUsedByMe = pmc.WorkingSetSize;
	}
}
DWORDLONG Ram::GetTotalVirtualMEM() { return totalVirtualMem; }
DWORDLONG Ram::GetUsedVirtualMEM() { return virtualMemUsed; }
DWORDLONG Ram::GetProcUsedVirtualMEM() { return virtualMemUsedByMe; }
DWORDLONG Ram::GetTotalMEM() { return totalPhysMem; }
DWORDLONG Ram::GetUsedMEM() { return physMemUsed; }
DWORDLONG Ram::GetProcUsedMEM() { return physMemUsedByMe; }