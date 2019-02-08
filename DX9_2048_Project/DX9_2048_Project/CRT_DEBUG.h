#ifndef __CRT_DEBUG_H__
#define __CRT_DEBUG_H__
#define _CRTDBG_MAP_ALLOC

#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )

#else
#define DBG_NEW new
#endif

#endif

// Memory Leak Check
//	_CrtSetBreakAlloc(164);