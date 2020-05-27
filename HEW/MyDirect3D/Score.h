#pragma once
#include "MyDirect3D.h"

class Score
{
	LPDIRECT3DDEVICE9 m_pDevice;
	LPDIRECT3DTEXTURE9 m_texture;
	D3DXVECTOR2 m_pos;
	int m_score;
public:
	void Initialize();
	void Upate();
	void Draw();
	void Finalize();
	void AddScore(int score);
	void SetPosition(D3DXVECTOR2 pos);
	int GetScore();
};

