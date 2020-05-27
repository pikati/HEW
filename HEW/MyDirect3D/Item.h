#pragma once
#include "MyDirect3D.h"

enum ITEM_TYPE {
	TAIYAKI,
	MERONPAN
};

struct ItemInfo {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scale;
	ITEM_TYPE	type;
	bool		enable;
	bool		hit;
	ItemInfo(D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scl, ITEM_TYPE newType, bool ena, bool hi)
	{
		this->pos = position;
		this->rot = rotation;
		this->scale = scl;
		this->type = newType;
		this->enable = ena;
		this->hit = hi;
	}
	ItemInfo()
	{
		this->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		this->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		this->scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		this->type = TAIYAKI;
		this->enable = false;
		this->hit = false;
	}
};

class Item
{
protected:
	D3DXVECTOR3	m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_scale;
	D3DXVECTOR3	m_playerPos;
	ITEM_TYPE	m_type;
	bool		m_bEnable;
	bool		m_bHit;
public:
	~Item() {};
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Hit() = 0;
	virtual bool IsEnable() = 0;
	virtual void SetPosition(D3DXVECTOR3 pos) = 0;
	virtual void SetRotation(D3DXVECTOR3 rot) = 0;
	virtual void SetScale(D3DXVECTOR3 scale) = 0;
	virtual D3DXVECTOR3	GetPosition() = 0;
	virtual D3DXVECTOR3	GetRotation() = 0;
	virtual D3DXVECTOR3	GetScale() = 0;
	virtual ItemInfo GetInfo() = 0;
	virtual void SetPlayerPos(D3DXVECTOR3 pos) = 0;
};

