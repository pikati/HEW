#pragma once

#include "Polygons.h"

#define COMBO_WIDTH 64
#define COMBO_HEIGHT 64

#define COMBO_TEX_WIDTH 0.2f
#define COMBO_TEX_HEIGHT 0.5f

class Combo
{
private:
	int		m_combo;
	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 m_scale;
	LPDIRECT3DDEVICE9 m_pDevice;
	LPDIRECT3DTEXTURE9 m_texture1;
	LPDIRECT3DTEXTURE9 m_texture2;
public:
	void Initialize();
	void Draw();
	void Finalize();
	void CountUp();
	void CountReset();
	int  GetCombo();
	void SetPosition(D3DXVECTOR2 pos);
};

