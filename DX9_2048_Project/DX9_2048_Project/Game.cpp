#include "Game.h"
#include "Defines.h"
#include <iostream>
#pragma warning(disable:4477)
#pragma warning(disable:4244)

RECT tilePosition[4][4];

void Game::Render()
{
	device->BeginScene();
	device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xFFFFFFFF, 1.0f, 0);
	UINT numPass;

	mainShader->SetMatrix("OrthoMatrix", &orthoMatrix);
	mainShader->Begin(&numPass, NULL);
	{
		for (UINT i = 0; i < numPass; i++)
		{
			mainShader->BeginPass(i);
			{
				testObject.Draw(mainShader);
				for (int i = 0; i < 4; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						testTile[i][j].Draw(mainShader);
					}
				}
			}
			mainShader->EndPass();
		}
	}
	mainShader->End();

	DrawInfo();

	device->EndScene();
	device->Present(0, 0, 0, 0);
}


void Game::Initialize
(int _screenX, int _screenY, HINSTANCE _hInstance, HINSTANCE _prevInstance, LPSTR _cmdLine, int _showCmd)
{
	debugConsole.SetFunction("Game::Initialize");
	debugConsole.Initialize(CONSOLESIZE_X, CONSOLESIZE_Y);
	mouse.Initialize();
	memory.Initialize();
	cpu.Initialize();
	keyboard.Initialize();
	mainTimer.Initialize();
	window.Initialize(_screenX, _screenY, _hInstance, _prevInstance, _cmdLine, _showCmd);
	D3DXInitialize();



	{
		tilePosition[0][0].bottom = 83;		tilePosition[0][0].top = 225;
		tilePosition[0][0].right = -174;	tilePosition[0][0].left = -318;

		tilePosition[1][0].bottom = -80;	tilePosition[1][0].top = 62;
		tilePosition[1][0].right = -174;	tilePosition[1][0].left = -318;

		tilePosition[2][0].bottom = -243;	tilePosition[2][0].top = -101;
		tilePosition[2][0].right = -174;	tilePosition[2][0].left = -318;

		tilePosition[3][0].bottom = -406;	tilePosition[3][0].top = -264;
		tilePosition[3][0].right = -174;	tilePosition[3][0].left = -318;

		tilePosition[0][1].bottom = 83;		tilePosition[0][1].top = 225;
		tilePosition[0][1].right = -11;	tilePosition[0][1].left = -155;

		tilePosition[1][1].bottom = -80;	tilePosition[1][1].top = 62;
		tilePosition[1][1].right = -11;	tilePosition[1][1].left = -155;

		tilePosition[2][1].bottom = -243;	tilePosition[2][1].top = -101;
		tilePosition[2][1].right = -11;	tilePosition[2][1].left = -155;

		tilePosition[3][1].bottom = -406;	tilePosition[3][1].top = -264;
		tilePosition[3][1].right = -11;	tilePosition[3][1].left = -155;

		tilePosition[0][2].bottom = 83;		tilePosition[0][2].top = 225;
		tilePosition[0][2].right = 152;	tilePosition[0][2].left = 8;

		tilePosition[1][2].bottom = -80;	tilePosition[1][2].top = 62;
		tilePosition[1][2].right = 152;	tilePosition[1][2].left = 8;

		tilePosition[2][2].bottom = -243;	tilePosition[2][2].top = -101;
		tilePosition[2][2].right = 152;	tilePosition[2][2].left = 8;

		tilePosition[3][2].bottom = -406;	tilePosition[3][2].top = -264;
		tilePosition[3][2].right = 152;	tilePosition[3][2].left = 8;

		tilePosition[0][3].bottom = 83;		tilePosition[0][3].top = 225;
		tilePosition[0][3].right = 315;	tilePosition[0][3].left = 171;

		tilePosition[1][3].bottom = -80;	tilePosition[1][3].top = 62;
		tilePosition[1][3].right = 315;	tilePosition[1][3].left = 171;

		tilePosition[2][3].bottom = -243;	tilePosition[2][3].top = -101;
		tilePosition[2][3].right = 315;	tilePosition[2][3].left = 171;

		tilePosition[3][3].bottom = -406;	tilePosition[3][3].top = -264;
		tilePosition[3][3].right = 315;	tilePosition[3][3].left = 171;
	}
	

	TextureLoad("main_screen", "Data\\Image\\main_screen.jpg");
	TextureLoad("2", "Data\\Image\\2.jpg");
	TextureLoad("4", "Data\\Image\\4.jpg");
	TextureLoad("8", "Data\\Image\\8.jpg");
	TextureLoad("16", "Data\\Image\\16.jpg");
	TextureLoad("32", "Data\\Image\\32.jpg");
	TextureLoad("64", "Data\\Image\\64.jpg");
	TextureLoad("128", "Data\\Image\\128.jpg");
	TextureLoad("256", "Data\\Image\\256.jpg");
	TextureLoad("512", "Data\\Image\\512.jpg");
	TextureLoad("1024", "Data\\Image\\1024.jpg");
	TextureLoad("2048", "Data\\Image\\2048.jpg");

	testObject.Initialize("main_screen", WINDOWSIZE_Y / 2, -WINDOWSIZE_Y / 2, WINDOWSIZE_X / 2, -WINDOWSIZE_X / 2);

	testTile[0][0].Initialize("2", tilePosition[0][0]);
	testTile[1][0].Initialize("4", tilePosition[1][0]);
	testTile[2][0].Initialize("8", tilePosition[2][0]);
	testTile[3][0].Initialize("16", tilePosition[3][0]);

	testTile[0][1].Initialize("32", tilePosition[0][1]);
	testTile[1][1].Initialize("64", tilePosition[1][1]);
	testTile[2][1].Initialize("128", tilePosition[2][1]);
	testTile[3][1].Initialize("256", tilePosition[3][1]);

	testTile[0][2].Initialize("512", tilePosition[0][2]);
	testTile[1][2].Initialize("1024", tilePosition[1][2]);
	testTile[2][2].Initialize("2048", tilePosition[2][2]);
	testTile[3][2].Initialize("2", tilePosition[3][2]);

	testTile[0][3].Initialize("2", tilePosition[0][3]);
	testTile[1][3].Initialize("4", tilePosition[1][3]);
	testTile[2][3].Initialize("8", tilePosition[2][3]);
	testTile[3][3].Initialize("16", tilePosition[3][3]);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			boardData[i][j] = 0;
	}


	avgFPS.Initialize(AVG);
	debugConsole << con::info << con::func << "End init" << con::endl;
	debugConsole.RestoreFunction();
	debugConsole << ">> ";
}

void Game::D3DXInitialize()
{
	debugConsole.SetFunction("Game::InitializeD3DX");

	IDirect3D9* d3d9 = 0;
	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d9)
	{
		debugConsole << con::error << con::func << "Direct3DCreate9() - failed" << con::endl;
		debugConsole << con::error << con::func << "critical error is detected" << con::endl;
		return;
	}

	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	int vp = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	d3d9->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_A8R8G8B8, false, D3DMULTISAMPLE_16_SAMPLES, NULL);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = window.winSize.right;
	d3dpp.BackBufferHeight = window.winSize.bottom;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = window.hwnd;
	d3dpp.Windowed = TRUE;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	//D3DPRESENT_INTERVAL_IMMEDIATE
	//D3DPRESENT_INTERVAL_DEFAULT
	if (FAILED(d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window.hwnd, vp, &d3dpp, &device)))
	{
		debugConsole << con::error << con::func << "CreateDevice() - D3DFMT_D24S8 failed" << con::endl;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16; // 16 - bit Buffer
		if (FAILED(d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window.hwnd, vp, &d3dpp, &device)))
		{
			d3d9->Release();
			debugConsole << con::error << con::func << "CreateDevice() - D3DFMT_D16 failed" << con::endl;
			debugConsole << con::error << con::func << "critical error is detected" << con::endl;
		}
	}
	d3d9->Release();
	D3DCAPS9 Caps;
	device->GetDeviceCaps(&Caps);
	mrt = Caps.NumSimultaneousRTs;

	debugConsole << con::info << con::func << "Default font loaded" << con::endl;
	D3DXCreateFont(device, 15, 0, FW_DONTCARE, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "system", &font);

	ShaderLoad("MainShader.fx", mainShader);

	D3DXMatrixOrthoRH(&orthoMatrix, window.winSize.right, window.winSize.bottom, ORTHO_NEAR, ORTHO_FAR);

	debugConsole << con::info << con::func << "End init" << con::endl;
	debugConsole.RestoreFunction();
}

void Game::RunGame()
{
//		if (PeekMessage(&window.msg, 0, 0, 0, PM_REMOVE)) 

	while (GetMessage(&window.msg, 0, 0, 0) && bRunGame) 
	{
		TranslateMessage(&window.msg);
		DispatchMessage(&window.msg);

		debugConsole.Input();
		keyboard.KeyEvent();
		Render();
	}
}

void Game::Release()
{
	debugConsole.SetFunction("Game::Release");
	debugConsole << con::info << con::func << "End Game" << con::endl;
	mouse.Release();
	avgFPS.Release();
	mainTimer.Release();
	memory.Release();
	cpu.Release();
	keyboard.Release();
	window.Release();
	for (auto ptr = texture.begin(); ptr != texture.end(); ptr++)
	{
		Release_<IDirect3DTexture9*>(ptr->second);
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			testTile[i][j].Release();
		}
	}

	testObject.Release();
	Release_<ID3DXFont*>(font);
	Release_<LPD3DXEFFECT>(mainShader);
	Release_<IDirect3DDevice9*>(device);
	debugConsole.Release();
}

LRESULT Game::MessageHandler
(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_msg)
	{
	case WM_DESTROY:
		EndGame();
		break;

	case WM_CLOSE:
		EndGame();
		break;

	case WM_CREATE:
		break;

	case WM_PAINT:
		break;

	case WM_MOUSEWHEEL:
		mouse.IsMouseWheel(_wParam);
		break;

	case WM_MOUSEMOVE:
		mouse.MouseMove(_lParam);
		break;

	case WM_RBUTTONDOWN:
		mouse.MouseDown(MOUSE_RIGHT, _lParam);
		break;

	case WM_LBUTTONDOWN:
		mouse.MouseDown(MOUSE_LEFT, _lParam);
		break;

	case WM_RBUTTONUP:
		mouse.MouseUp(MOUSE_RIGHT, _lParam);
		break;

	case WM_LBUTTONUP:
		mouse.MouseUp(MOUSE_LEFT, _lParam);
		break;

	case WM_KEYDOWN:
		keyboard.KeyDown(_wParam);
		break;

	case WM_KEYUP:
		keyboard.KeyUp(_wParam);
		break;

	}
	return DefWindowProc(_hwnd, _msg, _wParam, _lParam);
}

void Game::DrawInfo()
{
	avgFPS.Count();
	memory.Update();
	cpu.Update();
	sprintf_s(str, sizeof(str) / sizeof(char), TEXT("RUN time : %.03lf"), mainTimer.getTime());
	MsgPrint(0, 0);
	sprintf_s(str, sizeof(str) / sizeof(char), TEXT("AVG FPS : %4.03lf"), avgFPS.Get());
	MsgPrint(15, 0);
	sprintf_s(str, sizeof(str) / sizeof(char), TEXT("Fram Count : %u"), avgFPS.GetCount());
	MsgPrint(30, 0);
	sprintf_s(str, sizeof(str) / sizeof(char), TEXT("Total Virtual RAM : %dMB"), memory.GetTotalVirtualMEM() / (1024 * 1024));
	MsgPrint(45, 0);
	sprintf_s(str, sizeof(str) / sizeof(char), TEXT("Used Virtual RAM : %dMB"), memory.GetUsedVirtualMEM() / (1024 * 1024));
	MsgPrint(60, 0);
	sprintf_s(str, sizeof(str) / sizeof(char), TEXT("Total RAM : %dMB"), memory.GetTotalMEM() / (1024 * 1024));
	MsgPrint(75, 0);
	sprintf_s(str, sizeof(str) / sizeof(char), TEXT("Used RAM : %dMB"), memory.GetUsedMEM() / (1024 * 1024));
	MsgPrint(90, 0);
	sprintf_s(str, sizeof(str) / sizeof(char), TEXT("Proc RAM : %.03fMB"), (float)memory.GetProcUsedMEM() / (1024 * 1024));
	MsgPrint(105, 0);
	sprintf_s(str, sizeof(str) / sizeof(char), TEXT("Proc Virtual RAM : %.03fMB"), (float)memory.GetProcUsedVirtualMEM() / (1024 * 1024));
	MsgPrint(120, 0);
	sprintf_s(str, sizeof(str) / sizeof(char), TEXT("Total CPU : %d%%"), cpu.GetCpuUsage());
	MsgPrint(135, 0);
	sprintf_s(str, sizeof(str) / sizeof(char), TEXT("Proc CPU : %.1lf%%"), cpu.GetProcessUsage());
	MsgPrint(150, 0);
}

void Game::MsgPrint(const unsigned int _x, const unsigned int _y)
{
	FontBox.top = _x;
	FontBox.left = _y;
	font->DrawText(NULL, str, -1, &FontBox, DT_NOCLIP, D3DCOLOR_XRGB(0, 0, 0));
}

void Game::ShaderLoad(std::string _name, LPD3DXEFFECT & _shader)
{
	debugConsole.SetFunction("Game::ShaderLoad");

	LPD3DXBUFFER error = NULL;
	DWORD shaderflags = 0;

#if _DEBUG
	shaderflags |= D3DXSHADER_DEBUG;
#endif

	D3DXCreateEffectFromFile(device, _name.c_str(), NULL, NULL, shaderflags, NULL, &_shader, &error);
	if (!_shader && error)
	{
		char *ack = (char*)error->GetBufferPointer();
		debugConsole << ack << con::endl;
		getchar();
		debugConsole << con::error << con::func << "D3DXCreateEffectFromFile() error - " << _name << con::endl;
		//error handling
	}
	debugConsole.RestoreFunction();
}

void Game::TextureLoad(std::string _filename, std::string _filepath)
{
	debugConsole.SetFunction("Game::TextureLoad");
	texture[_filename] = NULL;
	if (FAILED(D3DXCreateTextureFromFile
	(device, _filepath.c_str(), &texture[_filename])))
	{
		debugConsole << con::error << con::func << "D3DXCreateTextureFromFile() error" << con::endl;
		debugConsole << con::error << con::func << "path : " << _filepath << con::endl;
		EndGame();
	}
	debugConsole.RestoreFunction();
}

void Game::EndGame()
{
	debugConsole << con::endl;
	bRunGame = false;
}



Game::Game()
{
}


Game::~Game()
{
}
