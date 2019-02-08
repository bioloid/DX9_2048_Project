#ifndef __TIME_H__
#define __TIME_H__
#include <Windows.h>
class Timer
{
private:
	ULONGLONG startTime;
public:
	Timer();
	~Timer();
	void Initialize();
	void Release();
	void ResetTime();
	float getTime();
};
#endif