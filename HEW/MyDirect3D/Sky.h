#pragma once
#include "XManager.h"
#include "MyDirect3D.h"
class Sky
{
private:
	LPDIRECT3DDEVICE9	m_pDevice;
	XManager			*m_x;

public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
};

