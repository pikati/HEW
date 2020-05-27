#pragma once
#include "MyDirect3D.h"
#include "Fbx.h"

class WinLose
{
private:
	Fbx*	m_fbx;
	D3DXVECTOR3* m_pos;
	int m_win;
	int m_lose;
public:
	void Initialize();
	void Update();
	void Draw(int idx);
	void Finalize();
	void SetPosition(D3DXVECTOR3 pos, int idx);
	void Win(int idx);
};

