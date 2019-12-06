#pragma once
#include "MyDirect3D.h"
#include "XManager.h"
class Goal
{
private:
	D3DXVECTOR3 m_pos;
	XManager*	m_pXManager;
public:
	void Initialize(D3DXVECTOR3 pos);
	void Update();
	void Draw();
	void Finalize();
	bool IsGoal(D3DXVECTOR3 targetPos);
};

