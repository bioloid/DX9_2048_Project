#ifndef __FPS_H__
#define __FPS_H__
#include "Timer.h"
#define INST true
#define AVG false
#define RESETCOUNT 256
class FPS
{
private:
	Timer time;
	bool mode;
	unsigned int frameCount;
public:
	FPS();
	~FPS();
	void Initialize(bool);
	void Release();
	void Reset();
	void Count();
	float Get();
	unsigned int GetCount();
};

#endif