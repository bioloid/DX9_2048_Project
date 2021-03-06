#include <iostream>
#include "CPU.h"
#include "Game.h"
#pragma warning(disable:4244)
CPU::CPU()
{
}

CPU::~CPU()
{
}

void CPU::Initialize()
{
	game.debugConsole.SetFunction("CPU::Initialize");

	PDH_STATUS status; // Initialize the flag indicating whether this object can read the system cpu usage or not.
	m_canReadCpu = true; // Create a query object to poll cpu usage.
	status = PdhOpenQuery(NULL, 0, &m_queryHandle);
	if (status != ERROR_SUCCESS)
	{
		m_canReadCpu = false;
		game.debugConsole << con::error << con::func << "PdhOpenQuery error" << con::endl;
		game.debugConsole << con::error << con::func << "CPU info is now disabled" << con::endl;

	} // Set query object to poll all cpus in the system.
	status = PdhAddCounter(m_queryHandle, TEXT("\\Processor(_Total)\\% processor time"), 0, &m_counterHandle);
	if (status != ERROR_SUCCESS)
	{
		m_canReadCpu = false;
		game.debugConsole << con::error << con::func << "PdhAddCounter error" << con::endl;
		game.debugConsole << con::error << con::func << "CPU info is now disabled" << con::endl;
	}
	m_lastSampleTime = GetTickCount();
	m_cpuUsage = 0;

	GetSystemInfo(&sysInfo);
	numProcessors = sysInfo.dwNumberOfProcessors;

	GetSystemTimeAsFileTime(&ftime);
	memcpy(&lastCPU, &ftime, sizeof(FILETIME));

	self = GetCurrentProcess();
	GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
	memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
	memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));
	game.debugConsole << con::info << con::func << "End init" << con::endl;
	game.debugConsole.RestoreFunction();
}
void CPU::Release()
{
	if (m_canReadCpu)
		PdhCloseQuery(m_queryHandle);
}
void CPU::Update()
{
	PDH_FMT_COUNTERVALUE value;
	if (m_canReadCpu)
	{
		if ((m_lastSampleTime + REFRESHTIME) < GetTickCount())
		{
			m_lastSampleTime = GetTickCount();
			PdhCollectQueryData(m_queryHandle);
			PdhGetFormattedCounterValue(m_counterHandle, PDH_FMT_LONG, NULL, &value);
			m_cpuUsage = value.longValue;

			GetSystemTimeAsFileTime(&ftime);
			memcpy(&now, &ftime, sizeof(FILETIME));

			GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
			memcpy(&sys, &fsys, sizeof(FILETIME));
			memcpy(&user, &fuser, sizeof(FILETIME));
			percent = (sys.QuadPart - lastSysCPU.QuadPart) + (user.QuadPart - lastUserCPU.QuadPart);
			percent /= (now.QuadPart - lastCPU.QuadPart);
			percent /= numProcessors;
			percent *= 100;
			lastCPU = now;
			lastUserCPU = user;
			lastSysCPU = sys;
		}
	}
}
int CPU::GetCpuUsage()
{
	int usage = 0;
	if (m_canReadCpu)
		usage = (int)m_cpuUsage;
	return usage;
}
float CPU::GetProcessUsage()
{
	return percent;
}