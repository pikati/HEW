#pragma once
#include "MyDirect3D.h"
#include "Polygons.h"
#include "Score.h"

class DispResult
{
private:
	LPDIRECT3DDEVICE9 m_pDevice;
	LPDIRECT3DTEXTURE9 m_tex;
	Score*	m_score;
public:
	void Initialize(int idx);
	void Draw(int idx);
	void Finalize();
	void SetScore(int s);
};

