#pragma once
#include "MyDirect3D.h"

class AABB
{
private:
	D3DXVECTOR3 m_max;
	D3DXVECTOR3 m_min;
	D3DXVECTOR3 m_pos;
	LINE_VERTEX m_v[14];
public:
	void Initialize(D3DXVECTOR3 min, D3DXVECTOR3 max, D3DXVECTOR3 pos);
	void Update(const D3DXVECTOR3& position);
	D3DXVECTOR3 GetMax();
	D3DXVECTOR3 GetMin();
	D3DXVECTOR3 GetPosition();
	void Draw();
};

