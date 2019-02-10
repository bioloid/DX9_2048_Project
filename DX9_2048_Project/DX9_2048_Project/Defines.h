#ifndef __MAINHEADER_H__
#define __MAINHEADER_H__

#define	WINDOWSIZE_X	1600
#define WINDOWSIZE_Y	900

#define CONSOLESIZE_X	600 
#define CONSOLESIZE_Y	900

#define ORTHO_NEAR		0.0f
#define ORTHO_FAR		1.0f


#define SCREEN_BASE_COLOR 0xFFFBF8EF // alpha 251 248 239 (RGB)
#define SCREEN_WORD_COLOR 0xFF7C756D // alpha 124 117 109 (RGB)



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