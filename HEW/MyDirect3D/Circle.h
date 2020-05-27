#pragma once
#include "MyDirect3D.h"
class Circle
{
private:
	D3DXVECTOR3 m_pos;
	float		m_radius;
public:
	void		SetPosition(D3DXVECTOR3 newPos);
	void		SetRudius(float newRudius);
	D3DXVECTOR3 GetPosition();
	float		GetRudius();
};

