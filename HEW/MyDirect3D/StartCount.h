#pragma once
#include "MyDirect3D.h"
#include "Polygons.h"

#define START_WIDTH 256
#define START_HEIGHT 256

#define START_TEX_WIDTH 0.2f
#define START_TEX_HEIGHT 0.5f

class StartCount
{
private:
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 m_scale;
	LPDIRECT3DDEVICE9 m_pDevice;
	LPDIRECT3DTEXTURE9 m_texture1;
	LPDIRECT3DTEXTURE9 m_texture2;
	int m_frame;
	int m_count;
	bool m_start;
	bool m_startEnd;
	bool m_end;
public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	bool IsStart();
};

