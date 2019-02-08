#ifndef __RAM_H__
#define __RAM_H__
#include <Windows.h>
#include <psapi.h>
#include "cpu.h"
class Ram
{
public:
	Ram();
	~Ram();
	void Initialize();
	void Release();
	void Update();
	DWORDLONG GetTotalVirtualMEM();
	DWORDLONG GetUsedVirtualMEM();
	DWORDLONG GetProcUsedVirtualMEM();
	DWORDLONG GetTotalMEM();
	DWORDLONG GetUsedMEM();
	DWORDLONG GetProcUsedMEM();

private:
	PROCESS_MEMORY_COUNTERS_EX g_mc;
	PROCESS_MEMORY_COUNTERS_EX pmc;
	SIZE_T virtualMemUsedByMe;
	SIZE_T physMemUsedByMe;
	DWORDLONG totalPhysMem;
	DWORDLONG physMemUsed;
	DWORDLONG virtualMemUsed;
	DWORDLONG totalVirtualMem;
	MEMORYSTATUSEX memInfo;

	unsigned long m_lastSampleTime = 0;
};
#endif