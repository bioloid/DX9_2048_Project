#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <string>
class Object
{
private:
	struct VertexXYZTEX;
	std::string textureName;
	IDirect3DVertexBuffer9* VB;
	D3DXMATRIXA16 worldMatrix;
	int sizeX, sizeY;
	unsigned int score;
public:
	void Initialize(std::string _filename, int _top, int _bottom, int _right, int _left);
	void Initialize(std::string _filename, RECT& _position);
	unsigned int GetScore();
	void Release();
	void Draw(LPD3DXEFFECT& shader);
	void ChangeTexture(std::string _filename);
	RECT GetPosition();
	void Move(int _top, int _bottom, int _right, int _left);
	void Move(RECT& _position);
	//	Object(Object& _newObject);
	Object();
	~Object();
};
struct Object::VertexXYZTEX
{
	VertexXYZTEX() {}
	VertexXYZTEX(float x, float y, float z, float u, float v)
	{
		_x = x;  _y = y;  _z = z;
		_u = u;  _v = v;
	}
	float _x, _y, _z, _u, _v;
	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX1;
};
#endif