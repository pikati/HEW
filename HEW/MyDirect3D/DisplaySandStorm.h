#pragma once
#include "MyDirect3D.h"

class DisplaySandStorm
{
private:
	LPDIRECT3DDEVICE9 m_pDevice;
	LPDIRECT3DTEXTURE9 m_texture;
	bool p1;
public:
	void Initialize();
	void Draw();
	void Finalize();
	void SetPlayer(bool b);
};

