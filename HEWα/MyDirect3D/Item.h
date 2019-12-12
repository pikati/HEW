#pragma once
#include "XManager.h"
#include "MyDirect3D.h"

class Item
{
protected:
	XManager*	m_pXmanager;
	D3DXVECTOR3	m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_scale;
public:
	~Item() {};
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Finalize() = 0;
	virtual void SetPosition(D3DXVECTOR3 pos) = 0;
	virtual void SetRotation(D3DXVECTOR3 rot) = 0;
	virtual void SetScale(D3DXVECTOR3 scale) = 0;
	virtual COBBTree& GetOBB() const = 0;
	virtual D3DXMATRIX* GetMatrix() = 0;
};

