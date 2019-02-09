#include "Game.h"
#include "Defines.h"
#pragma warning(disable:4477)

void Game::Render()
{
	device->BeginScene();
	device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, SCREEN_BASE_COLOR, 1.0f, 0);
	UINT numPass;
	mainShader->SetMatrix("OrthoMatrix", &orthoMatrix);
	mainShader->SetTexture("SamplingTexture", texture["Default"]);
	mainShader->Begin(&numPass, NULL);
	{
		for (UINT i = 0; i < numPass; i++)
		{
			mainShader->BeginPass(i);
			{
				
			}
			mainShader->EndPass();
		}
	}
	mainShader->End();

	DrawInfo();

	device->EndScene();
	device->Present(0, 0, 0, 0);
}

void Game::DrawInfo()
{
	avgFPS.Count();
	instFPS.Count();
	memory.Update();
	cpu.Update();
	sprintf_s(str, sizeof(str) / sizeof(char), TEXT("RUN time : %.03lf"), mainTimer.getTime());
	MsgPrint(0, 0);
	sprintf_s(str, sizeof(str) / sizeof(char), TEXT("AVG FPS : %4.03lf"), avgFPS.Get());
	MsgPrint(15, 0);
	sprintf_s(str, sizeof(str) / sizeof(char), TEXT("INST FPS : %4.03lf"), instFPS.Get());
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

void Game::TextureLoad(std::string _name, IDirect3DTexture9 * _texture)
{
	debugConsole.SetFunction("Game::TextureLoad");
	if (FAILED(D3DXCreateTextureFromFile
	(device, _name.c_str(), &_texture)))
	{
		debugConsole << con::error << con::func << "D3DXCreateTextureFromFile() error" << con::endl;
		debugConsole << con::error << con::func << "path : " << _name << con::endl;
		EndGame();
	}
	debugConsole.RestoreFunction();
}

void Game::EndGame()
{
	debugConsole << con::endl;
	bRunGame = false;
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


	texture["Default"] = NULL;
	TextureLoad("Data\\Default\\Texture\\defaultTexture.png", texture["Default"]);


	avgFPS.Initialize(AVG);
	instFPS.Initialize(INST);
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
	while (bRunGame) {
		if (PeekMessage(&window.msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&window.msg);
			DispatchMessage(&window.msg);
		}
		else {
			debugConsole.Input();
			keyboard.KeyEvent();
			Render();
		}
	}
}

void Game::Release()
{
	debugConsole.SetFunction("Game::Release");
	debugConsole << con::info << con::func << "End Game" << con::endl;
	mouse.Release();
	avgFPS.Release();
	instFPS.Release();
	mainTimer.Release();
	memory.Release();
	cpu.Release();
	keyboard.Release();
	window.Release();
	for (auto ptr = texture.begin(); ptr != texture.end(); ptr++)
	{
		Release_<IDirect3DTexture9*>(ptr->second);
	}

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




Game::Game()
{
}


Game::~Game()
{
}
