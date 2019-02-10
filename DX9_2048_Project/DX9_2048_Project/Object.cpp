#include "Game.h"
#include "Object.h"
#include <iostream>

void Object::Initialize
(std::string _filename, std::string _filepath, 
int _top, int _bottom, int _right, int _left) // 450 -450 800 -800
{
	game.debugConsole.SetFunction("Object::Initialize");
	textureName = _filename;
	game.TextureLoad(_filename, _filepath);


	D3DXMatrixIdentity(&worldMatrix);
	worldMatrix._41 = (_right + _left) / 2.0f;
	worldMatrix._42 = (_top + _bottom) / 2.0f;



	Object::VertexXYZTEX* data_;
	game.device->CreateVertexBuffer(6 * sizeof(Object::VertexXYZTEX), D3DUSAGE_WRITEONLY, Object::VertexXYZTEX::FVF, D3DPOOL_MANAGED, &VB, 0);
	if (VB == NULL)
	{
		game.debugConsole << con::error << con::func << "CreateVertexBuffer() - failed" << con::endl;
	}
	sizeX = _right - _left;
	sizeY = _top - _bottom;

	VB->Lock(0, 0, (void**)&data_, 0);
	data_[0] = Object::VertexXYZTEX(-sizeX / 2.0f,  sizeY / 2.0f, 0.0f, 0.0f, 0.0f);
	data_[1] = Object::VertexXYZTEX( sizeX / 2.0f,  sizeY / 2.0f, 0.0f, 1.0f, 0.0f);
	data_[2] = Object::VertexXYZTEX( sizeX / 2.0f, -sizeY / 2.0f, 0.0f, 1.0f, 1.0f);

	data_[3] = Object::VertexXYZTEX(-sizeX / 2.0f,  sizeY / 2.0f, 0.0f, 0.0f, 0.0f);
	data_[4] = Object::VertexXYZTEX( sizeX / 2.0f, -sizeY / 2.0f, 0.0f, 1.0f, 1.0f);
	data_[5] = Object::VertexXYZTEX(-sizeX / 2.0f, -sizeY / 2.0f, 0.0f, 0.0f, 1.0f);
	VB->Unlock();

	game.debugConsole.RestoreFunction();
}

void Object::Release()
{
	VB->Release();
	textureName.~basic_string();
}

void Object::Draw(LPD3DXEFFECT& shader)
{
	shader->SetTexture("SamplingTexture", game.texture[textureName]);
	shader->SetMatrix("WorldMatrix", &worldMatrix);
	shader->CommitChanges();

	game.device->SetFVF(Object::VertexXYZTEX::FVF);
	game.device->SetStreamSource(0, VB, 0, sizeof(Object::VertexXYZTEX));
	game.device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 6);

}

RECT Object::GetPosition()
{
	RECT Output;
	Output.top		 = worldMatrix._42 + sizeY/2;
	Output.bottom	 = worldMatrix._42 - sizeY/2;
	Output.right	 = worldMatrix._41 + sizeX/2;
	Output.left		 = worldMatrix._41 - sizeX/2;
	return Output;
}

void Object::Move(int _top, int _bottom, int _right, int _left)
{
	worldMatrix._41 = (_right + _left) / 2.0f;
	worldMatrix._42 = (_top + _bottom) / 2.0f;
}

Object::Object()
{
}


Object::~Object()
{
}
