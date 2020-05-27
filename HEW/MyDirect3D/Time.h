#pragma once
#include "MyDirect3D.h"
#include "Polygons.h"

#define TIME_WIDTH 100
#define TIME_HEIGHT 100

#define TIME_TEX_WIDTH 0.2f
#define TIME_TEX_HEIGHT 0.5f

class Time
{
private:
	
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 m_scale;
	LPDIRECT3DDEVICE9 m_pDevice;
	LPDIRECT3DTEXTURE9 m_texture;

	int m_frame;
	int m_time;

public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	int GetTime();
};

