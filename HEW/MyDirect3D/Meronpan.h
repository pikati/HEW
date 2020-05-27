#pragma once
#include "Item.h"

class Meronpan :
	public Item
{
public:
	Meronpan();
	~Meronpan();

	virtual void Initialize();
	virtual void Update();
	virtual void Hit();
	virtual bool IsEnable();
	virtual void SetPosition(D3DXVECTOR3 pos);
	virtual void SetRotation(D3DXVECTOR3 rot);
	virtual void SetScale(D3DXVECTOR3 scale);
	virtual D3DXVECTOR3	GetPosition();
	virtual D3DXVECTOR3	GetRotation();
	virtual D3DXVECTOR3	GetScale();
	virtual ItemInfo GetInfo();
	virtual void SetPlayerPos(D3DXVECTOR3 pos);
};

