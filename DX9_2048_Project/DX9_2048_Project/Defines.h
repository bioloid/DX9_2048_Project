#ifndef __MAINHEADER_H__
#define __MAINHEADER_H__

#define	WINDOWSIZE_X 1024
#define WINDOWSIZE_Y 1024

#define CONSOLESIZE_X 600 
#define CONSOLESIZE_Y 1024
//	Safe Release
//
template<class T> void Release_(T t)
{
	if (t != NULL)
	{
		t->Release();
		t = NULL;
	}
}
#endif