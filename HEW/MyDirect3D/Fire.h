#pragma once
#include "Obst.h"

class Fire : public Obst
{
private:
public:
	Fire();
	~Fire();
	virtual void	Initialize();
	virtual void	Update();
	virtual void	Hit();
	virtual bool	IsEnable();
	virtual void	CreateObstacle(D3DXVECTOR3 pos);
	virtual float*	CreateRondam(float* random);
	virtual void	SetPlayerPos(D3DXVECTOR3 pos);
	virtual void	SetPosition(D3DXVECTOR3 pos);
	virtual void	SetRotation(D3DXVECTOR3 rot);
	virtual void	SetScale(D3DXVECTOR3 scale);
	virtual D3DXVECTOR3 GetPosition();
	virtual D3DXVECTOR3 GetRotation();
	virtual D3DXVECTOR3 GetScale();
	virtual ObstacleInfo GetInfo();
	virtual void	Reset();
	virtual OBST_TYPE	GetElem();
};

